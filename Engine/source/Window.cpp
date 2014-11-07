
#include <Engine\Window.h>
#include <cassert>

/*
	PRIVATE
*/
const std::wstring Window::WndClassname = L"MyWindowClass";
const std::wstring Window::WndDefaultTitle = L"MyWindow";

const WNDPROC Window::WndProc =
[](HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) -> LRESULT
{
	Window* wnd = nullptr;

	if (msg == WM_CREATE)
	{
		wnd = static_cast<Window*>(reinterpret_cast<CREATESTRUCTW*>(lp)->lpCreateParams);
		SetWindowLongPtrW(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(wnd));
	}
	else
	{
		wnd = reinterpret_cast<Window*>(GetWindowLongPtrW(hwnd, GWLP_USERDATA));
	}

	return wnd ? wnd->processMessage(msg, wp, lp) : DefWindowProcW(hwnd, msg, wp, lp);
};

void Window::RegisterWindowClass()
{
	WNDCLASSEXW wc = { 0 };
	wc.cbSize = sizeof(wc);
	wc.cbWndExtra = sizeof(Window*);
	wc.hInstance = GetModuleHandleW(nullptr);
	wc.lpszClassName = WndClassname.c_str();
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = WndProc;
	assert(RegisterClassExW(&wc));
}

/*
	PUBLIC
*/
Window::Window(const glm::ivec2& wndSize, const std::wstring& wndTitle)
{
	if (m_WndCount++ == 0)
	{
		Window::RegisterWindowClass();
	}

	DWORD style = WS_CAPTION | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SYSMENU | WS_SIZEBOX;

	m_HWnd = CreateWindowExW(0, Window::WndClassname.c_str(), wndTitle.c_str(), style,
		CW_USEDEFAULT, CW_USEDEFAULT, 0, 0, nullptr, nullptr, GetModuleHandleW(nullptr), this);

	setSize(wndSize);
	setVisible(true);
}

Window::~Window()
{
	DestroyWindow(m_HWnd);

	if (--m_WndCount == 0)
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
			
			/* TEMP - Placeholder data*/
			e.msg = msg;
			e.wp = wp;
			e.lp = lp;
			/**/

			m_Events.push(std::move(e));
			return 0;
		}
		default:
			return DefWindowProcW(m_HWnd, msg, wp, lp);
	}
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
