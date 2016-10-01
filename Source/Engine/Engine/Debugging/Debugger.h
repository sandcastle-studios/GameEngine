#pragma once

namespace ENGINE_NAMESPACE
{
	class Debugger
	{
	public:
		Debugger(void * aWindowHandle);
		~Debugger();

		void NewFrame();
		void RenderFrame();
	};
}
