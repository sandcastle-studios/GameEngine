#include "stdafx.h"
#include "Debugger.h"
#include "Engine\Imgui\imgui_impl_dx11.h"
#include <imgui.h>
#include "Engine\Buffer\VertexBuffer.h"

namespace ENGINE_NAMESPACE
{
	Debugger::Debugger(void * aWindowHandle)
	{
		bool initialized = ImGui_ImplDX11_Init(aWindowHandle, Engine::GetInstance().GetRenderer().GetDevice(), Engine::GetInstance().GetRenderer().GetContext());

		myLineEffect = std::make_shared<Effect>();
		myLineEffect->AttachVertexShader("shaders/debugging/line.fx", "VShader");
		myLineEffect->AttachPixelShader("shaders/debugging/line.fx", "PShader");
		InputLayout layout;
		layout.Add("POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT);
		layout.Add("COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT);
		myLineEffect->Link(layout);

		myLineVertexBuffer = std::make_shared<VertexBuffer<LineVertex>>(nullptr, 2, false);
	}

	void Debugger::DrawLine(const Vector3f & aFrom, const Vector3f & aTo, const Vector4f & aColor)
	{
		std::array<LineVertex, 2> vertices;
		vertices[0].position = Vector4f(aFrom, 1.f);
		vertices[0].color = aColor;
		vertices[1].position = Vector4f(aTo, 1.f);
		vertices[1].color = aColor;
		
		myLineVertexBuffer->UpdateData(&vertices[0], 2, false);
		myLineVertexBuffer->Bind(0);
		
		myLineEffect->Bind();
		Engine::GetInstance().GetRenderer().GetContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
		Engine::GetInstance().GetRenderer().GetContext()->Draw(2, 0);
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
}
