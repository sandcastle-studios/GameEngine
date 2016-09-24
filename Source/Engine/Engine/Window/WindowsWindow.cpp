#include "stdafx.h"
#include "Engine\Window\WindowsWindow.h"
#include "Engine\Window\WindowMessage.h"
#include <iostream>
#include <imgui.h>

extern IMGUI_API LRESULT ImGui_ImplDX11_WndProcHandler(HWND, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT CALLBACK WindowProc(HWND aHwnd, UINT aMessage, WPARAM aWParam, LPARAM aLParam)
{
	ImGui_ImplDX11_WndProcHandler(aHwnd, aMessage, aWParam, aLParam);

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

template <template<KeyboardKey> typename TMessageType, typename ...TArguments>
void PostKeyboardMessage(KeyboardKey aKey, const TArguments &...args)
{
	switch (aKey)
	{
	case KeyboardKey::eSpace:
		PostMaster::Post<TMessageType<KeyboardKey::eSpace>>(TMessageType<KeyboardKey::eSpace>(args...));
		break;
	case KeyboardKey::eEscape:
		PostMaster::Post<TMessageType<KeyboardKey::eEscape>>(TMessageType<KeyboardKey::eEscape>(args...));
		break;
	case KeyboardKey::eReturn:
		PostMaster::Post<TMessageType<KeyboardKey::eReturn>>(TMessageType<KeyboardKey::eReturn>(args...));
		break;
	case KeyboardKey::eNum0:
		PostMaster::Post<TMessageType<KeyboardKey::eNum0>>(TMessageType<KeyboardKey::eNum0>(args...));
		break;
	case KeyboardKey::eNum1:
		PostMaster::Post<TMessageType<KeyboardKey::eNum1>>(TMessageType<KeyboardKey::eNum1>(args...));
		break;
	case KeyboardKey::eNum2:
		PostMaster::Post<TMessageType<KeyboardKey::eNum2>>(TMessageType<KeyboardKey::eNum2>(args...));
		break;
	case KeyboardKey::eNum3:
		PostMaster::Post<TMessageType<KeyboardKey::eNum3>>(TMessageType<KeyboardKey::eNum3>(args...));
		break;
	case KeyboardKey::eNum4:
		PostMaster::Post<TMessageType<KeyboardKey::eNum4>>(TMessageType<KeyboardKey::eNum4>(args...));
		break;
	case KeyboardKey::eNum5:
		PostMaster::Post<TMessageType<KeyboardKey::eNum5>>(TMessageType<KeyboardKey::eNum5>(args...));
		break;
	case KeyboardKey::eNum6:
		PostMaster::Post<TMessageType<KeyboardKey::eNum6>>(TMessageType<KeyboardKey::eNum6>(args...));
		break;
	case KeyboardKey::eNum7:
		PostMaster::Post<TMessageType<KeyboardKey::eNum7>>(TMessageType<KeyboardKey::eNum7>(args...));
		break;
	case KeyboardKey::eNum8:
		PostMaster::Post<TMessageType<KeyboardKey::eNum8>>(TMessageType<KeyboardKey::eNum8>(args...));
		break;
	case KeyboardKey::eNum9:
		PostMaster::Post<TMessageType<KeyboardKey::eNum9>>(TMessageType<KeyboardKey::eNum9>(args...));
		break;
	case KeyboardKey::eA:
		PostMaster::Post<TMessageType<KeyboardKey::eA>>(TMessageType<KeyboardKey::eA>(args...));
		break;
	case KeyboardKey::eB:
		PostMaster::Post<TMessageType<KeyboardKey::eB>>(TMessageType<KeyboardKey::eB>(args...));
		break;
	case KeyboardKey::eC:
		PostMaster::Post<TMessageType<KeyboardKey::eC>>(TMessageType<KeyboardKey::eC>(args...));
		break;
	case KeyboardKey::eD:
		PostMaster::Post<TMessageType<KeyboardKey::eD>>(TMessageType<KeyboardKey::eD>(args...));
		break;
	case KeyboardKey::eE:
		PostMaster::Post<TMessageType<KeyboardKey::eE>>(TMessageType<KeyboardKey::eE>(args...));
		break;
	case KeyboardKey::eF:
		PostMaster::Post<TMessageType<KeyboardKey::eF>>(TMessageType<KeyboardKey::eF>(args...));
		break;
	case KeyboardKey::eG:
		PostMaster::Post<TMessageType<KeyboardKey::eG>>(TMessageType<KeyboardKey::eG>(args...));
		break;
	case KeyboardKey::eH:
		PostMaster::Post<TMessageType<KeyboardKey::eH>>(TMessageType<KeyboardKey::eH>(args...));
		break;
	case KeyboardKey::eI:
		PostMaster::Post<TMessageType<KeyboardKey::eI>>(TMessageType<KeyboardKey::eI>(args...));
		break;
	case KeyboardKey::eJ:
		PostMaster::Post<TMessageType<KeyboardKey::eJ>>(TMessageType<KeyboardKey::eJ>(args...));
		break;
	case KeyboardKey::eK:
		PostMaster::Post<TMessageType<KeyboardKey::eK>>(TMessageType<KeyboardKey::eK>(args...));
		break;
	case KeyboardKey::eL:
		PostMaster::Post<TMessageType<KeyboardKey::eL>>(TMessageType<KeyboardKey::eL>(args...));
		break;
	case KeyboardKey::eM:
		PostMaster::Post<TMessageType<KeyboardKey::eM>>(TMessageType<KeyboardKey::eM>(args...));
		break;
	case KeyboardKey::eN:
		PostMaster::Post<TMessageType<KeyboardKey::eN>>(TMessageType<KeyboardKey::eN>(args...));
		break;
	case KeyboardKey::eO:
		PostMaster::Post<TMessageType<KeyboardKey::eO>>(TMessageType<KeyboardKey::eO>(args...));
		break;
	case KeyboardKey::eP:
		PostMaster::Post<TMessageType<KeyboardKey::eP>>(TMessageType<KeyboardKey::eP>(args...));
		break;
	case KeyboardKey::eQ:
		PostMaster::Post<TMessageType<KeyboardKey::eQ>>(TMessageType<KeyboardKey::eQ>(args...));
		break;
	case KeyboardKey::eR:
		PostMaster::Post<TMessageType<KeyboardKey::eR>>(TMessageType<KeyboardKey::eR>(args...));
		break;
	case KeyboardKey::eS:
		PostMaster::Post<TMessageType<KeyboardKey::eS>>(TMessageType<KeyboardKey::eS>(args...));
		break;
	case KeyboardKey::eT:
		PostMaster::Post<TMessageType<KeyboardKey::eT>>(TMessageType<KeyboardKey::eT>(args...));
		break;
	case KeyboardKey::eU:
		PostMaster::Post<TMessageType<KeyboardKey::eU>>(TMessageType<KeyboardKey::eU>(args...));
		break;
	case KeyboardKey::eV:
		PostMaster::Post<TMessageType<KeyboardKey::eV>>(TMessageType<KeyboardKey::eV>(args...));
		break;
	case KeyboardKey::eW:
		PostMaster::Post<TMessageType<KeyboardKey::eW>>(TMessageType<KeyboardKey::eW>(args...));
		break;
	case KeyboardKey::eX:
		PostMaster::Post<TMessageType<KeyboardKey::eX>>(TMessageType<KeyboardKey::eX>(args...));
		break;
	case KeyboardKey::eY:
		PostMaster::Post<TMessageType<KeyboardKey::eY>>(TMessageType<KeyboardKey::eY>(args...));
		break;
	case KeyboardKey::eZ:
		PostMaster::Post<TMessageType<KeyboardKey::eZ>>(TMessageType<KeyboardKey::eZ>(args...));
		break;

	case KeyboardKey::eF1:
		PostMaster::Post<TMessageType<KeyboardKey::eF1>>(TMessageType<KeyboardKey::eF1>(args...));
		break;
	case KeyboardKey::eF2:
		PostMaster::Post<TMessageType<KeyboardKey::eF2>>(TMessageType<KeyboardKey::eF2>(args...));
		break;
	case KeyboardKey::eF3:
		PostMaster::Post<TMessageType<KeyboardKey::eF3>>(TMessageType<KeyboardKey::eF3>(args...));
		break;
	case KeyboardKey::eF4:
		PostMaster::Post<TMessageType<KeyboardKey::eF4>>(TMessageType<KeyboardKey::eF4>(args...));
		break;
	case KeyboardKey::eF5:
		PostMaster::Post<TMessageType<KeyboardKey::eF5>>(TMessageType<KeyboardKey::eF5>(args...));
		break;
	case KeyboardKey::eF6:
		PostMaster::Post<TMessageType<KeyboardKey::eF6>>(TMessageType<KeyboardKey::eF6>(args...));
		break;
	case KeyboardKey::eF7:
		PostMaster::Post<TMessageType<KeyboardKey::eF7>>(TMessageType<KeyboardKey::eF7>(args...));
		break;
	case KeyboardKey::eF8:
		PostMaster::Post<TMessageType<KeyboardKey::eF8>>(TMessageType<KeyboardKey::eF8>(args...));
		break;
	case KeyboardKey::eF9:
		PostMaster::Post<TMessageType<KeyboardKey::eF9>>(TMessageType<KeyboardKey::eF9>(args...));
		break;
	case KeyboardKey::eF10:
		PostMaster::Post<TMessageType<KeyboardKey::eF10>>(TMessageType<KeyboardKey::eF10>(args...));
		break;
	case KeyboardKey::eF11:
		PostMaster::Post<TMessageType<KeyboardKey::eF11>>(TMessageType<KeyboardKey::eF11>(args...));
		break;
	case KeyboardKey::eF12:
		PostMaster::Post<TMessageType<KeyboardKey::eF12>>(TMessageType<KeyboardKey::eF12>(args...));
		break;

	case KeyboardKey::eControl:
		PostMaster::Post<TMessageType<KeyboardKey::eControl>>(TMessageType<KeyboardKey::eControl>(args...));
		break;
	case KeyboardKey::eAlt:
		PostMaster::Post<TMessageType<KeyboardKey::eAlt>>(TMessageType<KeyboardKey::eAlt>(args...));
		break;
	case KeyboardKey::eShift:
		PostMaster::Post<TMessageType<KeyboardKey::eShift>>(TMessageType<KeyboardKey::eShift>(args...));
		break;

	case KeyboardKey::eLeft:
		PostMaster::Post<TMessageType<KeyboardKey::eLeft>>(TMessageType<KeyboardKey::eLeft>(args...));
		break;
	case KeyboardKey::eRight:
		PostMaster::Post<TMessageType<KeyboardKey::eRight>>(TMessageType<KeyboardKey::eRight>(args...));
		break;
	case KeyboardKey::eUp:
		PostMaster::Post<TMessageType<KeyboardKey::eUp>>(TMessageType<KeyboardKey::eUp>(args...));
		break;
	case KeyboardKey::eDown:
		PostMaster::Post<TMessageType<KeyboardKey::eDown>>(TMessageType<KeyboardKey::eDown>(args...));
		break;

	case KeyboardKey::eNone:
		break;

	default:
		Error(FormatString("Invalid key passed to PostKeyboardMessage (WindowsWindow) {0})", static_cast<int>(aKey)));
	}
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
		if (message.data.keyEvent.repeatCount == 1)
		{
			PostKeyboardMessage<KeyDownMessage>(message.data.keyEvent.key, message.data.keyEvent.key);
			PostMaster::Post(AnyKeyDownMessage(message.data.keyEvent.key));
		}
		PostKeyboardMessage<KeyRepeatMessage>(message.data.keyEvent.key, message.data.keyEvent.key, message.data.keyEvent.repeatCount);
		PostMaster::Post(AnyKeyRepeatMessage(message.data.keyEvent.key, message.data.keyEvent.repeatCount));
		break;
	case WM_KEYUP:
		message.type = WindowMessageType::eKeyUp;
		message.data.keyEvent.key = ConvertVirtualKey(aWParam);
		PostKeyboardMessage<KeyUpMessage>(message.data.keyEvent.key, message.data.keyEvent.key);
		PostMaster::Post(AnyKeyUpMessage(message.data.keyEvent.key));
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
	case VK_LMENU:
		return KeyboardKey::eAlt;
	default:
		return KeyboardKey::eNone;
	}
}
