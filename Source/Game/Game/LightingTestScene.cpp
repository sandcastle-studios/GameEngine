#include "stdafx.h"
#include "LightingTestScene.h"
#include <Engine\Model\AssimpModel.h>
#include <Engine\Model\ModelInstance.h>
#include <Engine\Effect\StandardEffect.h>
#include <Engine\Camera\Camera.h>
#include <Engine\Rendering\DXRenderer.h>
#include <Engine\Rendering\ModelRenderer.h>
#include <imgui.h>
#include <Engine\Camera\Controllers\FreeSpaceCameraController.h>


LightingTestScene::LightingTestScene()
{
	PushCameraController(std::make_shared<SB::FreeSpaceCameraController>(5.f, 1.5f));

	std::shared_ptr<SB::AssimpModel> model = std::make_shared<SB::AssimpModel>("models/Modelviewer_Exempelmodell/K11_1415.fbx");
	myHead = std::make_shared<SB::ModelInstance>(model);
	
	myHead->SetMatrix(SB::Matrix44f::CreateTranslation(0.f, 0.f, -5.f));

	auto bb = myHead->GetBoundingBox();

	SetCameraOrientation(bb.GetCenter() + SB::Vector3f(0.f, 0.f, -bb.GetSize().z * 1.5f));
	
	SB::Engine::GetRenderer().GetModelRenderer().SetDirectionalLight(0, SB::Vector3f(0.f, 1.f, .5f), SB::Vector4f(0.7f, 0.7f, 0.7f, 1.f));
}

LightingTestScene::~LightingTestScene()
{
}

void LightingTestScene::Update(const SB::Time & aDeltaTime)
{
	ImGui::SetNextWindowPos({ 16, 16 }, ImGuiSetCond_Once);
	ImGui::SetNextWindowSize({ 375, 400 }, ImGuiSetCond_Once);
	ImGui::SetNextWindowCollapsed(true, ImGuiSetCond_Once);

	if (ImGui::Begin("Debug Window"))
	{
		static bool checked;
		ImGui::Checkbox("Checked", &checked);
	}

	ImGui::End();

	// myHead->SetMatrix(Matrix44f::CreateRotateAroundY(myTime.InSeconds()));
	

	Scene::Update(aDeltaTime);
}

void LightingTestScene::Render()
{
	Scene::Render();
}
