
#include <Engine/Context.h>
#include <stdexcept>
#include <vector>

#include <Engine/Util.h>

#ifdef _DEBUG
const GLDEBUGPROC Context::DebugProc = [](GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{
	char* sourceStr   = nullptr;
	char* typeStr     = nullptr;
	char* severityStr = nullptr;

	switch (source)
	{
	case GL_DEBUG_SOURCE_API:             sourceStr = "API";             break;
	case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   sourceStr = "WINDOW SYSTEM";   break;
	case GL_DEBUG_SOURCE_SHADER_COMPILER: sourceStr = "SHADER COMPILER"; break;
	case GL_DEBUG_SOURCE_THIRD_PARTY:     sourceStr = "THIRD PARTY";     break;
	case GL_DEBUG_SOURCE_APPLICATION:     sourceStr = "APPLICATION";     break;
	case GL_DEBUG_SOURCE_OTHER:           sourceStr = "OTHER";           break;
	default:                              sourceStr = "UNKNOWN";         break;
	}

	switch (type)
	{
	case GL_DEBUG_TYPE_ERROR:               typeStr = "ERROR";              break;
	case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: typeStr = "BEHAVIOR";           break;
	case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  typeStr = "UNDEFINED_BEHAVIOR"; break;
	case GL_DEBUG_TYPE_PORTABILITY:         typeStr = "PORTABILITY";        break;
	case GL_DEBUG_TYPE_PERFORMANCE:         typeStr = "PERFORMANCE";        break;
	case GL_DEBUG_TYPE_MARKER:              typeStr = "MARKER";             break;
	case GL_DEBUG_TYPE_PUSH_GROUP:          typeStr = "PUSH GROUP";         break;
	case GL_DEBUG_TYPE_POP_GROUP:           typeStr = "POP GROUP";          break;
	case GL_DEBUG_TYPE_OTHER:               typeStr = "OTHER";              break;
	default:                                typeStr = "UNKNOWN";            break;
	}

	switch (severity)
	{
	case GL_DEBUG_SEVERITY_HIGH:         severityStr = "HIGH";         break;
	case GL_DEBUG_SEVERITY_MEDIUM:       severityStr = "MEDIUM";       break;
	case GL_DEBUG_SEVERITY_LOW:          severityStr = "LOW";          break;
	case GL_DEBUG_SEVERITY_NOTIFICATION: severityStr = "NOTIFICATION"; break;
	default:                             severityStr = "UNKNOWN";      break;
	}

	std::fprintf(stderr, "\nOpenGL Error (%s, %s, %s, %u)\n\t%s\n", severityStr, sourceStr, typeStr, id, message);
};
#endif

Context::Context(HWND hwnd, const ContextSettings& settings)
{
	// If a null window handle was provided, there's nothing to be done
	if (hwnd == nullptr)
	{
		throw std::runtime_error("Error: Cannot create opengl context from a null window handle.");
	}

	m_WindowHandle = hwnd;
	m_DeviceContext = GetDC(m_WindowHandle);

	// Create temporary context for setup purposes. (Required by the following steps)
	HGLRC tempContext = nullptr;
	{
		PIXELFORMATDESCRIPTOR pfd;
		memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
		pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
		pfd.nVersion = 1;
		pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
		pfd.iPixelType = LPD_TYPE_RGBA;
		pfd.cColorBits = settings.ColorBits;
		pfd.cDepthBits = settings.DepthBits;
		pfd.cStencilBits = settings.StencilBits;
		pfd.iLayerType = PFD_MAIN_PLANE;

		int nFormat = ChoosePixelFormat(m_DeviceContext, &pfd);
		if (SetPixelFormat(m_DeviceContext, nFormat, &pfd) == 0)
		{
			throw std::runtime_error("Error: Unable to set the selected pixel format for the temporary context.");
		}

		tempContext = wglCreateContext(m_DeviceContext);
		if (tempContext == nullptr)
		{
			throw std::runtime_error("Error: Unable to create the temporary context.");
		}

		wglMakeCurrent(m_DeviceContext, tempContext);
	}
	
	// Initialize GLEW
	{
		static bool IsInitialized = false;

		if (!IsInitialized)
		{
			GLenum error = glewInit();

			if (error == GLEW_NO_ERROR)
			{
				IsInitialized = true;
			}
			else
			{
				std::fprintf(stderr, "GLEW Error: %s\n", glewGetErrorString(error));
				throw std::runtime_error("Error: Unable to initialize GLEW.");
			}
		}
	}

	// Get a valid pixel format
	int pixelFormat;
	if (settings.AntialiasLevel > 0)
	{
		int attributes[] =
		{
			WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
			WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
			WGL_ACCELERATION_ARB,	WGL_FULL_ACCELERATION_ARB,
			WGL_DOUBLE_BUFFER_ARB,	GL_TRUE,
			WGL_SAMPLE_BUFFERS_ARB,	1,
			WGL_SAMPLES_ARB,		settings.AntialiasLevel,
			0 // End
		};

		// TODO: Loop through multiple formats, instead of settling for the first

		UINT nFormats;
		if (wglChoosePixelFormatARB(m_DeviceContext, attributes, nullptr, 1, &pixelFormat, &nFormats) == 0)
		{
			pixelFormat = 0;
		}
	}
	
	// Fallback to a basic pixel format, if the extension doesn't work
	if (pixelFormat == 0)
	{
		PIXELFORMATDESCRIPTOR pfd;
		memset(&pfd, 0, sizeof(pfd));
		pfd.nSize = sizeof(pfd);
		pfd.nVersion = 1;
		pfd.iLayerType = PFD_MAIN_PLANE;
		pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
		pfd.iPixelType = PFD_TYPE_RGBA;
		pfd.cColorBits = settings.ColorBits;
		pfd.cDepthBits = settings.DepthBits;
		pfd.cStencilBits = settings.StencilBits;

		pixelFormat = ChoosePixelFormat(m_DeviceContext, &pfd);

		if (pixelFormat != 0)
		{
			SetPixelFormat(m_DeviceContext, pixelFormat, &pfd);
		}
	}

	// Get the current OpenGL version
	GLint majorVersion, minorVersion;
	glGetIntegerv(GL_MAJOR_VERSION, &majorVersion);
	glGetIntegerv(GL_MINOR_VERSION, &minorVersion);

	if (majorVersion > 3)
	{
		int attributes[] =
		{
			WGL_CONTEXT_MAJOR_VERSION_ARB,	majorVersion,
			WGL_CONTEXT_MINOR_VERSION_ARB,	minorVersion,
			WGL_CONTEXT_PROFILE_MASK_ARB,	WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB,
#ifdef _DEBUG
			// Enable debugging on the context
			WGL_CONTEXT_FLAGS_ARB,			WGL_CONTEXT_DEBUG_BIT_ARB,
#endif
			0 // End
		};

		m_RenderContext = wglCreateContextAttribsARB(m_DeviceContext, nullptr, attributes);
		wglMakeCurrent(nullptr, nullptr);
		wglDeleteContext(tempContext);
		wglMakeCurrent(m_DeviceContext, m_RenderContext);

#ifdef _DEBUG
		// Enable debug output and register a callback function
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallbackARB(Context::DebugProc, nullptr);
#endif
	}

	// If all else fails, use the basic OpenGL 2.x context
	if (m_RenderContext == nullptr)
	{
		m_RenderContext = tempContext;
	}
}

Context::~Context()
{
	// TODO: Clean up OpenGL resources. (Buffers, Arrays, Shaders, etc.)

	if (m_RenderContext == wglGetCurrentContext())
	{
		wglMakeCurrent(nullptr, nullptr);
	}

	wglDeleteContext(m_RenderContext);

	if (m_DeviceContext != nullptr)
	{
		ReleaseDC(m_WindowHandle, m_DeviceContext);
	}
}

void Context::setViewport(const glm::ivec2& position, const glm::ivec2& size) const
{
	glViewport(position.x, position.y, size.x, size.y);
}

void Context::clear(const glm::vec4& color, GLbitfield mask) const
{
	glClear(mask);
	glClearColor(color.r, color.g, color.b, color.a);
}

void Context::swap() const
{
	SwapBuffers(m_DeviceContext);
}
