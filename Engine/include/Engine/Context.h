
#ifndef CONTEXT_H
#define CONTEXT_H

#include <glm/glm.hpp>
#include <glew/glew.h>
#include <glew/wglew.h>

class Context final
{
public:
	Context(HWND);
	~Context();

	void setViewport(const glm::ivec2& position, const glm::ivec2& size) const;
	void clear(const glm::vec4& color = { 0, 0, 0, 0 }) const;
	void display() const;
private:
	HWND m_WindowHandle;
	HDC m_DeviceContext;
	HGLRC m_RenderContext;
};

#endif // EXAMPLE

