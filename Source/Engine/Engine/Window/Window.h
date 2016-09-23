#pragma once
#include "Engine\Size.h"

struct WindowMessage;

class Window
{
public:
	virtual ~Window();
	
	virtual void SetTitle(const std::string &aTitle) = 0;
	inline const std::string & GetTitle() const;

	virtual bool CanResize() const = 0;
	virtual void SetSize(const Size<int> &aSize) = 0;
	inline const Size<int> &GetSize() const;

	virtual bool PollMessage(WindowMessage & aMessage) = 0;
	virtual bool GetMessage(WindowMessage & aMessage) = 0;

	virtual void Open() = 0;
	virtual bool IsOpen() const = 0;
	virtual void Close() = 0;

	virtual void SetVisible(bool aIsVisible) = 0;
	virtual bool IsVisible() const;

	virtual void * GetHandle() const = 0;

protected:
	Window();

	void UpdateSize(const Size<int> &aNewSize);

private:
	std::string myTitle;
	Size<int> mySize;
	bool myIsVisible;
};

const std::string & Window::GetTitle() const
{
	return myTitle;
}

const Size<int> & Window::GetSize() const
{
	return mySize;
}
