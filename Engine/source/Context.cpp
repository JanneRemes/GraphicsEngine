
#include <Engine/Context.h>
#include <stdexcept>
#include <vector>

Context::Context(HWND hwnd)
{
	if (hwnd == nullptr)
	{
		throw std::runtime_error("Error: Cannot create opengl context from a null window handle.");
	}

	m_WindowHandle = hwnd;
	m_DeviceContext = GetDC(m_WindowHandle);

	PIXELFORMATDESCRIPTOR pfd;
	memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;
	pfd.iPixelType = LPD_TYPE_RGBA;
	pfd.cColorBits = 24; // n bit RGBA, excluding alpha
	pfd.cDepthBits = 24;
	pfd.cStencilBits = 8;
	pfd.iLayerType = PFD_MAIN_PLANE;

	int nFormat = ChoosePixelFormat(m_DeviceContext, &pfd);
	if (nFormat == 0)
	{
		throw std::runtime_error("Error: Unable to find suitable pixel format.");
	}

	int result = SetPixelFormat(m_DeviceContext, nFormat, &pfd);
	if (result == 0)
	{
		throw std::runtime_error("Error: Unable to set the selected pixel format.");
	}

	HGLRC tempContext = wglCreateContext(m_DeviceContext);
	wglMakeCurrent(m_DeviceContext, tempContext);

	GLenum error = glewInit();
	if (error != GLEW_NO_ERROR)
	{
		std::printf("Error: %s\n", glewGetErrorString(error));
		throw std::runtime_error("Error: Unable to initialize GLEW.");
	}

	if (glewIsSupported("WGL_ARB_create_context") == GL_TRUE)
	{
		auto version = glGetString(GL_VERSION);

		const int attribs[]
		{
			WGL_CONTEXT_MAJOR_VERSION_ARB, version[0] - '0',
			WGL_CONTEXT_MINOR_VERSION_ARB, version[2] - '0',
			WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
			0 // Null terminator
		};

		m_RenderContext = wglCreateContextAttribsARB(m_DeviceContext, nullptr, attribs);
		wglMakeCurrent(nullptr, nullptr);
		wglDeleteContext(tempContext);
		wglMakeCurrent(m_DeviceContext, m_RenderContext);
	}
	else
	{
		m_RenderContext = tempContext;
	}
}

Context::~Context()
{
	// TODO: Clean up OpenGL resources. (Buffers, Arrays, Shaders, etc.)

	wglMakeCurrent(m_DeviceContext, nullptr);
	wglDeleteContext(m_RenderContext);
	ReleaseDC(m_WindowHandle, m_DeviceContext);
}

void Context::setViewport(const glm::ivec2& position, const glm::ivec2& size) const
{
	glViewport(position.x, position.y, size.x, size.y);
}

void Context::clear(const glm::vec4& color) const
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glClearColor(color.r, color.g, color.b, color.a);
}

void Context::display() const
{
	SwapBuffers(m_DeviceContext);
}
