#pragma once
#include "Window.h"
#include <queue>
#include <Windows.h>
#include "WindowMessage.h"
#undef GetMessage

class WindowsWindow : public Window
{
public:
	WindowsWindow();
	~WindowsWindow();

	virtual void SetTitle(const std::string &aTitle) override;
	
	virtual bool CanResize() const override;
	
	virtual void SetSize(const Size<int> &aSize) override;
	virtual bool PollMessage(WindowMessage & aMessage) override;
	
	virtual bool GetMessage(WindowMessage & aMessage) override;
	
	virtual void Open() override;
	
	virtual bool IsOpen() const override;
	
	virtual void Close() override;
	
	virtual void SetVisible(bool aIsVisible) override;
		
	virtual void * GetHandle() const override;

	void ReceiveMessage(HWND aHwnd, UINT aMessage, WPARAM aWParam, LPARAM aLParam);

private:
	static KeyboardKey ConvertVirtualKey(const WPARAM & aVirtualKey);

	HWND myHandle;
	bool myIsOpen;
	WNDCLASSEX myWindowClass;
	std::queue<WindowMessage> myMessageQueue;
};

