
#ifndef CONTEXT_H
#define CONTEXT_H

#include <Engine/Window.h>
#include <glew/glew.h>

class Context
{
	static HWND hwnd;
	static HDC device;
	static HGLRC render;
public:
	static bool Init(const Window& wnd);
	static void Clear(const glm::vec4& color, unsigned int flags = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	static void Swap();
};

#endif // Include guard
