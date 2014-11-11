
#ifndef CONTEXT_H
#define CONTEXT_H

#include <glm/glm.hpp>
#include <glew/glew.h>
#include <glew/wglew.h>

#include <Engine/Window.h>
#include <Engine/ContextSettings.h>

class Context final
{
#ifdef _DEBUG
	static const GLDEBUGPROC DebugProc;
#endif
public:
	Context(const Window& wnd, const ContextSettings& settings = ContextSettings());
	~Context();

	void setViewport(const glm::ivec4& rect);
	void setViewport(const glm::ivec2& position, const glm::ivec2& size);
	void setViewport(int x, int y, int w, int h);
	void clear(const glm::vec4& color = { 0, 0, 0, 0 }, GLbitfield mask = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT) const;
	void swap() const;
private:
	HWND       m_WindowHandle  = nullptr;
	HDC        m_DeviceContext = nullptr;
	HGLRC      m_RenderContext = nullptr;
	glm::ivec4 m_ViewPort = { 0, 0, 800, 600 };

	// MSAA related variables
	bool       m_IsMSAA_Enabled = false;
	GLsizei    m_MSAA_Samples   = 0;
	GLuint     m_MSAA_Texture   = 0;
	GLuint     m_MSAA_FBO       = 0;
};

#endif // Include guard

