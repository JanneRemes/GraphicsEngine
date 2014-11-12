
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
	static void __stdcall DebugProc(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam);
#endif
public:
	Context(const Window& wnd, const ContextSettings& settings = ContextSettings());
	~Context();

	void clear(const glm::vec4& color = { 0, 0, 0, 0 }, GLbitfield mask = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT) const;
	void swap() const;
private:
	glm::ivec2 m_WndSize;
	HWND       m_WndHandle     = nullptr;
	HDC        m_DeviceContext = nullptr;
	HGLRC      m_RenderContext = nullptr;

	// MSAA related variables
	bool       m_MSAA_Enabled = false;
	GLsizei    m_MSAA_Samples = 0;
	GLuint     m_MSAA_Texture = 0;
	GLuint     m_MSAA_FBO     = 0;
};

#endif // Include guard

