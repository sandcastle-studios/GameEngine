#include "stdafx.h"
#include "WindowsWindow.h"
#include "WindowMessage.h"
#include <iostream>

LRESULT CALLBACK WindowProc(HWND aHwnd, UINT aMessage, WPARAM aWParam, LPARAM aLParam)
{
	WindowsWindow *wnd = reinterpret_cast<WindowsWindow*>(GetWindowLongPtr(aHwnd, GWLP_USERDATA));
	
	if (wnd != nullptr)
	{
		wnd->ReceiveMessage(aHwnd, aMessage, aWParam, aLParam);
	}

	switch (aMessage)
	{
	case WM_DESTROY:
	case WM_QUIT:
		PostQuitMessage(0);
		return 0;

	case WM_SYSCOMMAND:
		if ((aWParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
			return 0;
		break;
	}
	
	return DefWindowProc(aHwnd, aMessage, aWParam, aLParam);
}

WindowsWindow::WindowsWindow()
{
}

WindowsWindow::~WindowsWindow()
{
}

void WindowsWindow::SetTitle(const std::string &aTitle)
{
	if (IsOpen())
	{
		SetWindowTextA(myHandle, aTitle.c_str());
	}

	Window::SetTitle(aTitle);
}

bool WindowsWindow::CanResize() const
{
	return true;
}

void WindowsWindow::SetSize(const Size<int> &aSize)
{
	if (IsOpen())
	{
		RECT rect;
		GetWindowRect(myHandle, &rect);

		rect.right = rect.left + aSize.width;
		rect.bottom = rect.top + aSize.height;

		AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

		SetWindowPos(myHandle, HWND_TOP, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, 0);
	}

	Window::SetSize(aSize);
}

bool WindowsWindow::PollMessage(WindowMessage & aMessage)
{
	if (IsOpen())
	{
		MSG msg = { 0 };

		if (PeekMessage(&msg, myHandle, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	if (myMessageQueue.empty() == true)
	{
		return false;
	}

	aMessage = myMessageQueue.front();
	myMessageQueue.pop();
	return true;
}

bool WindowsWindow::GetMessage(WindowMessage & aMessage)
{
	if (IsOpen())
	{
		MSG msg = { 0 };

		if (GetMessageA(&msg, myHandle, 0, 0))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	if (myMessageQueue.empty() == true)
	{
		return false;
	}

	aMessage = myMessageQueue.front();
	myMessageQueue.pop();
	return true;
}

void WindowsWindow::Open()
{
	if (IsOpen())
	{
		return;
	}
	
	HINSTANCE mHandle = GetModuleHandle(nullptr);

	DWORD windowStyle = WS_OVERLAPPEDWINDOW;

	RECT rect;
	rect.left = 0;
	rect.right = GetSize().width;
	rect.top = 0;
	rect.bottom = GetSize().height;

	AdjustWindowRect(&rect, windowStyle, false);

	memset(&myWindowClass, 0, sizeof(WNDCLASSEX));
	myWindowClass.cbSize = sizeof(WNDCLASSEX);
	myWindowClass.style = CS_HREDRAW | CS_VREDRAW;
	myWindowClass.lpfnWndProc = WindowProc;
	myWindowClass.hInstance = mHandle;
	myWindowClass.hCursor = LoadCursorW(nullptr, IDC_ARROW);
	myWindowClass.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW);
	myWindowClass.lpszClassName = L"WindowClass";
	myWindowClass.hIcon = ::LoadIcon(mHandle, MAKEINTRESOURCE(101));
	myWindowClass.hIconSm = LoadIcon(mHandle, MAKEINTRESOURCE(101));
	RegisterClassEx(&myWindowClass);

	myHandle = CreateWindowExA(WS_EX_CLIENTEDGE, "WindowClass",
		GetTitle().c_str(),
		windowStyle,
		CW_USEDEFAULT, CW_USEDEFAULT,
		rect.right - rect.left + 4, rect.bottom - rect.top + 4,
		nullptr, nullptr, mHandle, nullptr);

	myIsOpen = true;
	
	SetWindowLongPtr(myHandle, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));

	// WM_CREATE is received before GWL_USERDATA is set, therefore queue a create-message manually
	ReceiveMessage(myHandle, WM_CREATE, 0, 0);

	SetVisible(IsVisible());

	Window::Open();
}

bool WindowsWindow::IsOpen() const
{
	return myIsOpen;
}

void WindowsWindow::Close()
{
	if (IsOpen() == false)
	{
		return;
	}

	CloseWindow(myHandle);
	myHandle = nullptr;

	myIsOpen = false;
	
	Window::Close();
}

void WindowsWindow::SetVisible(bool aIsVisible)
{
	if (IsOpen())
	{
		ShowWindow(myHandle, aIsVisible ? SW_SHOW : SW_HIDE);
	}

	Window::SetVisible(aIsVisible);
}

void * WindowsWindow::GetHandle() const
{
	return myHandle;
}

void WindowsWindow::ReceiveMessage(HWND aHwnd, UINT aMessage, WPARAM aWParam, LPARAM aLParam)
{
	WindowMessage message;

	switch (aMessage)
	{
	case WM_SIZE:
		message.type = WindowMessageType::eSizeChanged;
		message.data.resizeEvent.newSize.width = LOWORD(aLParam);
		message.data.resizeEvent.newSize.height = HIWORD(aLParam);
		UpdateSize(message.data.resizeEvent.newSize);
		break;
	case WM_CLOSE:
		message.type = WindowMessageType::eCloseButtonPressed;
		break;
	case WM_ENTERSIZEMOVE:
		message.type = WindowMessageType::eResizeBegins;
		break;
	case WM_EXITSIZEMOVE:
		message.type = WindowMessageType::eResizeEnds;
		break;
	case WM_PAINT:
		message.type = WindowMessageType::ePaint;
		break;
	case WM_CREATE:
		message.type = WindowMessageType::eCreate;
		break;
	case WM_DESTROY:
		message.type = WindowMessageType::eDestroy;
		break;
	default:
		memset(&message, 0, sizeof(message));
		break;
	}

	myMessageQueue.push(message);
}
