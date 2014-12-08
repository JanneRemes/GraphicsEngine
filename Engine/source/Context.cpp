
#include <Engine/Context.h>
#include <Engine/Util.h>
#include <Engine/GL.h>
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

	int format = ChoosePixelFormat(device, &pfd);
	if (format == 0)
		return false;

	bool result = SetPixelFormat(device, format, &pfd) == TRUE;
	if (!result)
		return false;

	HGLRC render = wglCreateContext(device);
	wglMakeCurrent(device, render);

	std::fprintf(stdout, "OpenGL Version: %s\n", gl::GetString(gl::VERSION));

	if (!render)
		return false;
	return true;
}

void Context::Clear(const glm::vec4& color, GLbitfield mask)
{
	gl::ClearColor(color.r, color.g, color.b, color.a);
	gl::Clear(mask);
}

void Context::Swap()
{
	SwapBuffers(device);
}
