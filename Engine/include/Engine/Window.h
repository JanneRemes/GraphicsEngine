
#ifndef WINDOW_H
#define WINDOW_H

#include <Windows.h>
#include <string>
#include <glm/glm.hpp>

class Window
{
	static const wchar_t* WndClassname;

	static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);
	static void RegisterWindowClass();
public:
	Window(const glm::ivec2& wndSize, const std::string& wndTitle);
	virtual ~Window();

	LRESULT processMessage(UINT msg, WPARAM wp, LPARAM lp);
	void update() const;

	void setPosition(const glm::ivec2& wndPosition);
	glm::ivec2 getPosition() const;

	void setSize(const glm::ivec2& wndSize);
	glm::ivec2 getSize() const;

	void setTitle(const std::wstring& wndTitle);
	std::string getTitle() const;

	void setVisible(bool visible);

	HWND getHandle() const;

	void close();
	bool isOpen() const;
private:
	HWND m_HWnd = nullptr;
	bool m_isOpen = true;
};

#endif // Include guard
