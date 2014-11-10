
#ifndef CONTEXT_H
#define CONTEXT_H

#include <glm/glm.hpp>
#include <glew/glew.h>
#include <glew/wglew.h>

#include <Engine/ContextSettings.h>

class Context final
{
#ifdef _DEBUG
	static const GLDEBUGPROC DebugProc;
#endif
public:
	Context(HWND hwnd, const ContextSettings& settings = ContextSettings());
	~Context();

	void setViewport(const glm::ivec2& position, const glm::ivec2& size) const;
	void clear(const glm::vec4& color = { 0, 0, 0, 0 }, GLbitfield mask = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT) const;
	void swap() const;
private:
	HWND m_WindowHandle;
	HDC m_DeviceContext;
	HGLRC m_RenderContext;
};

#endif // Include guard

