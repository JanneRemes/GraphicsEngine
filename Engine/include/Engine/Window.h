
#ifndef WINDOW_H
#define WINDOW_H

#include <string>
#include <glm/glm.hpp>
#include <Windows.h>
#include <queue>
#include <Engine/Event.h>

class Window
{
	static const std::wstring WndClassname;
	static const std::wstring WndDefaultTitle;
	static const WNDPROC WndProc;
	static void RegisterWindowClass();

public:
	Window(const glm::ivec2& wndSize, const std::wstring& wndTitle = Window::WndDefaultTitle);
	virtual ~Window();

	LRESULT processMessage(UINT msg, WPARAM wp, LPARAM lp);
	bool pollEvent(Event& out);

	void setPosition(const glm::ivec2& wndPosition);
	glm::ivec2 getPosition() const;

	void setSize(const glm::ivec2& wndSize);
	glm::ivec2 getSize() const;

	void setTitle(const std::wstring& wndTitle);
	std::wstring getTitle() const;

	void setVisible(bool visible);

	HWND getHandle() const;

	void close();
	bool isOpen() const;
private:
	HWND m_HWnd = nullptr;
	bool m_isOpen = true;
	size_t m_WndCount = 0;
	std::queue<Event> m_Events;
};

#endif // Include guard
