
#ifndef CONTEXT_H
#define CONTEXT_H

#include <wgl_core_2_1/wgl.h>
#include <Engine/Graphics.h>
#include <Engine/Window.h>

class Context
{
	static HWND hwnd;
	static HDC device;
	static HGLRC render;
public:
	static bool Init(const Window& wnd);
	static void Clear(const glm::vec4& color, unsigned int flags = gl::COLOR_BUFFER_BIT | gl::DEPTH_BUFFER_BIT | gl::STENCIL_BUFFER_BIT);
	static void Swap();
};

#endif // Include guard
