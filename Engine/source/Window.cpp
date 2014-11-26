
#include <Engine/Window.h>
#include <Engine/Util.h>

/*
	- PRIVATE STATIC -
*/

const wchar_t* Window::WndClassname = L"MyWindowClass";

LRESULT CALLBACK Window::WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
	// Get the pointer stored inside the window structure, and pass the message to it
	Window* wnd = reinterpret_cast<Window*>(GetWindowLongPtrW(hwnd, GWLP_USERDATA));
	return wnd ? wnd->processMessage(msg, wp, lp) : DefWindowProcW(hwnd, msg, wp, lp);
};

void Window::RegisterWindowClass()
{
	WNDCLASSEXW wc;
	memset(&wc, 0, sizeof(wc));
	wc.cbSize = sizeof(wc);
	wc.cbWndExtra = sizeof(Window*);
	wc.hInstance = GetModuleHandleW(nullptr);
	wc.lpszClassName = WndClassname;
	wc.lpfnWndProc = WndProc;
	wc.style = CS_OWNDC;
	RegisterClassExW(&wc);
}

/*
	- PUBLIC -
*/

Window::Window(const glm::ivec2& wndSize, const std::string& wndTitle)
{
	// If this was the first window, register the window class
	Window::RegisterWindowClass();

	// Measure the screen, and position the window to the center
	const glm::ivec2 screenSize(GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
	const DWORD style = WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU;

	RECT rect;
	rect.left = screenSize.x / 2 - wndSize.x / 2;
	rect.top = screenSize.y / 2 - wndSize.y / 2;
	rect.right = rect.left + wndSize.x;
	rect.bottom = rect.top + wndSize.y;
	AdjustWindowRectEx(&rect, style, 0, 0);

	// Create the window
	m_HWnd = CreateWindowExW(0, WndClassname, Util::Convert(wndTitle).c_str(), style,
		rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top,
		nullptr, nullptr, GetModuleHandleW(nullptr), this);

	// Store a pointer to this, inside the window structure
	SetWindowLongPtrW(m_HWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));

	// Show the window
	setVisible(true);
}

Window::~Window()
{
	// Destroy the window
	DestroyWindow(m_HWnd);
	UnregisterClassW(WndClassname, GetModuleHandleW(nullptr));
}

LRESULT Window::processMessage(UINT msg, WPARAM wp, LPARAM lp)
{
	switch (msg)
	{
	case WM_CLOSE:
		m_isOpen = false;
		break;
	}

	return DefWindowProcW(m_HWnd, msg, wp, lp);
}

void Window::update() const
{
	MSG msg;

	while (PeekMessageW(&msg, nullptr, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}
}

void Window::setPosition(const glm::ivec2& wndPosition)
{
	SetWindowPos(m_HWnd, nullptr, wndPosition.x, wndPosition.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
}

glm::ivec2 Window::getPosition() const
{
	RECT rect;
	GetWindowRect(m_HWnd, &rect);
	return glm::ivec2(rect.left, rect.top);
}

void Window::setSize(const glm::ivec2& wndSize)
{
	RECT rect = { 0, 0, wndSize.x, wndSize.y };
	AdjustWindowRect(&rect, GetWindowLongW(m_HWnd, GWL_STYLE), false);
	int width = rect.right - rect.left;
	int height = rect.bottom - rect.top;
	SetWindowPos(m_HWnd, nullptr, 0, 0, width, height, SWP_NOMOVE | SWP_NOZORDER);
}

glm::ivec2 Window::getSize() const
{
	RECT rect;
	GetClientRect(m_HWnd, &rect);
	return glm::ivec2(rect.right - rect.left, rect.bottom - rect.top);
}

void Window::setTitle(const std::wstring& wndTitle)
{
	SetWindowTextW(m_HWnd, wndTitle.c_str());
}

std::string Window::getTitle() const
{
	std::vector<wchar_t> buffer(GetWindowTextLengthW(m_HWnd));
	GetWindowTextW(m_HWnd, buffer.data(), buffer.size());
	return Util::Convert(std::wstring(buffer.begin(), buffer.end()));
}

void Window::setVisible(bool visible)
{
	ShowWindow(m_HWnd, visible ? SW_SHOW : SW_HIDE);
}

HWND Window::getHandle() const
{
	return m_HWnd;
}

void Window::close()
{
	m_isOpen = false;
}

bool Window::isOpen() const
{
	return m_isOpen;
}
