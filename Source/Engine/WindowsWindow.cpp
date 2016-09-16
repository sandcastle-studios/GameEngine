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
	case WM_KEYDOWN:
		message.type = WindowMessageType::eKeyDown;
		message.data.keyEvent.key = ConvertVirtualKey(aWParam);
		// Bit 0 - 15 is the repeat count
		message.data.keyEvent.repeatCount = static_cast<int>(static_cast<uint16_t>(aLParam));
		break;
	case WM_KEYUP:
		message.type = WindowMessageType::eKeyUp;
		message.data.keyEvent.key = ConvertVirtualKey(aWParam);
	default:
		memset(&message, 0, sizeof(message));
		break;
	}

	myMessageQueue.push(message);
}

KeyboardKey WindowsWindow::ConvertVirtualKey(const WPARAM & aVirtualKey)
{
	switch (aVirtualKey)
	{
	case 0x30:
		return KeyboardKey::eNum0;
	case 0x31:
		return KeyboardKey::eNum1;
	case 0x32:
		return KeyboardKey::eNum2;
	case 0x33:
		return KeyboardKey::eNum3;
	case 0x34:
		return KeyboardKey::eNum4;
	case 0x35:
		return KeyboardKey::eNum5;
	case 0x36:
		return KeyboardKey::eNum6;
	case 0x37:
		return KeyboardKey::eNum7;
	case 0x38:
		return KeyboardKey::eNum8;
	case 0x39:
		return KeyboardKey::eNum9;
	case 0x41:
		return KeyboardKey::eA;
	case 0x42:
		return KeyboardKey::eB;
	case 0x43:
		return KeyboardKey::eC;
	case 0x44:
		return KeyboardKey::eD;
	case 0x45:
		return KeyboardKey::eE;
	case 0x46:
		return KeyboardKey::eF;
	case 0x47:
		return KeyboardKey::eG;
	case 0x48:
		return KeyboardKey::eH;
	case 0x49:
		return KeyboardKey::eI;
	case 0x4A:
		return KeyboardKey::eJ;
	case 0x4B:
		return KeyboardKey::eK;
	case 0x4C:
		return KeyboardKey::eL;
	case 0x4D:
		return KeyboardKey::eM;
	case 0x4E:
		return KeyboardKey::eN;
	case 0x4F:
		return KeyboardKey::eO;
	case 0x50:
		return KeyboardKey::eP;
	case 0x51:
		return KeyboardKey::eQ;
	case 0x52:
		return KeyboardKey::eR;
	case 0x53:
		return KeyboardKey::eS;
	case 0x54:
		return KeyboardKey::eT;
	case 0x55:
		return KeyboardKey::eU;
	case 0x56:
		return KeyboardKey::eV;
	case 0x57:
		return KeyboardKey::eW;
	case 0x58:
		return KeyboardKey::eX;
	case 0x59:
		return KeyboardKey::eY;
	case 0x5A:
		return KeyboardKey::eZ;
	case VK_F1:
		return KeyboardKey::eF1;
	case VK_F2:
		return KeyboardKey::eF2;
	case VK_F3:
		return KeyboardKey::eF3;
	case VK_F4:
		return KeyboardKey::eF4;
	case VK_F5:
		return KeyboardKey::eF5;
	case VK_F6:
		return KeyboardKey::eF6;
	case VK_F7:
		return KeyboardKey::eF7;
	case VK_F8:
		return KeyboardKey::eF8;
	case VK_F9:
		return KeyboardKey::eF9;
	case VK_F10:
		return KeyboardKey::eF10;
	case VK_F11:
		return KeyboardKey::eF11;
	case VK_F12:
		return KeyboardKey::eF12;
	case VK_ESCAPE:
		return KeyboardKey::eEscape;
	case VK_RETURN:
		return KeyboardKey::eReturn;
	case VK_SPACE:
		return KeyboardKey::eSpace;
	case VK_CONTROL:
		return KeyboardKey::eControl;
	case VK_SHIFT:
		return KeyboardKey::eShift;
	case VK_LEFT:
		return KeyboardKey::eLeft;
	case VK_RIGHT:
		return KeyboardKey::eRight;
	case VK_UP:
		return KeyboardKey::eUp;
	case VK_DOWN:
		return KeyboardKey::eDown;
	default:
		return KeyboardKey::eNone;
	}
}
