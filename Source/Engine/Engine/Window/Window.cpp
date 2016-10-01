#include "stdafx.h"
#include "Engine\Window\Window.h"

namespace ENGINE_NAMESPACE
{
	bool Window::PollMessage(WindowMessage & aMessage)
	{
		return false;
	}

	bool Window::GetMessage(WindowMessage & aMessage)
	{
		return false;
	}

	void Window::Open()
	{
	}

	bool Window::IsOpen() const
	{
		return false;
	}

	void Window::Close()
	{
	}

	void Window::SetVisible(bool aIsVisible)
	{
		myIsVisible = aIsVisible;
	}

	bool Window::IsVisible() const
	{
		return myIsVisible;
	}

	void * Window::GetHandle() const
	{
		return nullptr;
	}

	Window::Window()
	{
		myTitle = "Unnamed Window";
		myIsVisible = true;
	}

	bool Window::CanResize() const
	{
		return false;
	}

	void Window::SetSize(const Size<int> &aSize)
	{
		mySize = aSize;
	}

	void Window::SetTitle(const std::string &aTitle)
	{
		myTitle = aTitle;
	}

	void Window::UpdateSize(const Size<int> &aNewSize)
	{
		mySize = aNewSize;
	}

	Window::~Window()
	{
	}
}
