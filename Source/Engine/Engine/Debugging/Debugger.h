#pragma once

class Debugger
{
public:
	Debugger(void * aWindowHandle);
	~Debugger();

	void NewFrame();
	void RenderFrame();
};
