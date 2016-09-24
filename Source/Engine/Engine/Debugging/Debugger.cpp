#include "stdafx.h"
#include "Debugger.h"
#include "Engine\Imgui\imgui_impl_dx11.h"
#include <imgui.h>

Debugger::Debugger(void * aWindowHandle)
{
	bool initialized = ImGui_ImplDX11_Init(aWindowHandle, Engine::GetInstance().GetRenderer().GetDevice(), Engine::GetInstance().GetRenderer().GetContext());
}

Debugger::~Debugger()
{
	ImGui_ImplDX11_Shutdown();
}

void Debugger::NewFrame()
{
	ImGui_ImplDX11_NewFrame();
}

void Debugger::RenderFrame()
{
	ImGui::Render();
}
