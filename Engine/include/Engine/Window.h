
#ifndef WINDOW_H
#define WINDOW_H

#include <Windows.h>
#include <string>
#include <queue>
#include <glm/glm.hpp>
#include <Engine/Event.h>

class Window
{
	static size_t WndCount;
	static const std::wstring WndClassname;
	static const std::wstring WndDefaultTitle;
	static const DWORD WndDefaultStyle;

	static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);
	static void RegisterWindowClass();
public:
	Window(const glm::ivec2& wndSize, const std::wstring& wndTitle = WndDefaultTitle, DWORD style = WndDefaultStyle);
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
	std::queue<Event> m_Events;
};

#endif // Include guard
