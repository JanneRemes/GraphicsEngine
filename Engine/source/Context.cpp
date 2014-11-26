
#include <Engine/Context.h>
#include <Engine/Util.h>
#include <Engine/Graphics.h>
#include <glew/wglew.h>
#include <iostream>

HWND Context::hwnd = nullptr;
HDC Context::device = nullptr;
HGLRC Context::render = nullptr;

bool Context::Init(const Window& wnd)
{
	if ((hwnd = wnd.getHandle()) == nullptr)
		return false;

	device = GetDC(hwnd);

	PIXELFORMATDESCRIPTOR pfd;
	memset(&pfd, 0, sizeof(pfd));
	pfd.nSize = sizeof(pfd);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = LPD_TYPE_RGBA;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 32;
	pfd.cStencilBits = 8;
	pfd.iLayerType = PFD_MAIN_PLANE;

	int format = GL::ChoosePixelFormat(device, pfd);
	if (format == 0)
		return false;

	bool result = GL::SetPixelFormat(device, format, pfd);
	if (!result)
		return false;

	HGLRC render = GL::CreateContext(device);
	GL::MakeCurrent(device, render);

	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		Util::ShowMessage("GLEW is not initialized!");
		return false;
	}

	std::fprintf(stdout, "OpenGL Version: %s\n", glGetString(GL_VERSION));

	if (!render)
		return false;
	return true;
}

void Context::Clear(const glm::vec4& color, unsigned int bits)
{
	GL::ClearColor(color);
	GL::Clear(bits);
}

void Context::Swap()
{
	SwapBuffers(device);
}
