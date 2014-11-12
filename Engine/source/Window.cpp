
#include <Engine\Window.h>

/*
	- PRIVATE STATIC -
*/

size_t Window::WndCount = 0;
const std::wstring Window::WndClassname = L"MyWindowClass";
const std::wstring Window::WndDefaultTitle = L"MyWindow";
const DWORD Window::WndDefaultStyle = WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU;

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
	wc.lpszClassName = WndClassname.c_str();
	wc.lpfnWndProc = WndProc;
	wc.style = CS_OWNDC;
	RegisterClassExW(&wc);
}

/*
	- PUBLIC -
*/

Window::Window(const glm::ivec2& wndSize, const std::wstring& wndTitle, DWORD style)
{
	// If this was the first window, register the window class
	if (WndCount++ == 0)
	{
		Window::RegisterWindowClass();
	}

	// Measure the screen, and position the window to the center
	const glm::ivec2 screenSize(GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));

	RECT rect;
	rect.left = screenSize.x / 2 - wndSize.x / 2;
	rect.top = screenSize.y / 2 - wndSize.y / 2;
	rect.right = rect.left + wndSize.x;
	rect.bottom = rect.top + wndSize.y;
	AdjustWindowRectEx(&rect, style, 0, 0);

	// Create the window
	m_HWnd = CreateWindowExW(0, Window::WndClassname.c_str(), wndTitle.c_str(), style,
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

	// If this was the last window, unregister the window class
	if (--WndCount == 0)
	{
		UnregisterClassW(Window::WndClassname.c_str(), GetModuleHandleW(nullptr));
	}
}

LRESULT Window::processMessage(UINT msg, WPARAM wp, LPARAM lp)
{
	switch (msg)
	{
		case WM_CLOSE:
		{
			Event e;
			e.type = Event::Closed;

			// TEMP - Placeholder data
			e.msg = msg;
			e.wp = wp;
			e.lp = lp;

			m_Events.push(std::move(e));
			return 0;
		}
	}

	return DefWindowProcW(m_HWnd, msg, wp, lp);
}

bool Window::pollEvent(Event& out)
{
	MSG msg;

	while (PeekMessageW(&msg, nullptr, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}

	if (!m_Events.empty())
	{
		out = m_Events.front();
		m_Events.pop();
		
		return true;
	}

	return false;
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

std::wstring Window::getTitle() const
{
	std::vector<wchar_t> buffer(GetWindowTextLengthW(m_HWnd));
	GetWindowTextW(m_HWnd, buffer.data(), buffer.size());
	return std::wstring(buffer.begin(), buffer.end());
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
