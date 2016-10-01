#include "stdafx.h"
#include "PbrTestScene.h"
#include <Engine\Model\AssimpModel.h>
#include <Engine\Model\ModelInstance.h>
#include <Engine\Effect\StandardEffect.h>
#include <Engine\Camera\Camera.h>
#include <Engine\Rendering\DXRenderer.h>
#include <Engine\Rendering\ModelRenderer.h>
#include <imgui.h>
#include <Engine\Component\Factory\ComponentFactory.h>
#include <Engine/Model/ModelInstance.h>
#include <Engine\Component\ModelComponent.h>
#include <Engine\GameObject\GameObject.h>
#include "..\Engine\Engine\Camera\Controllers\FreeSpaceCameraController.h"
#include "..\Engine\Engine\Model\CubeModel.h"
#include "..\Engine\Engine\SoundManager\SoundManger.h"

PbrTestScene::PbrTestScene()
	: Scene("PbrTestScene", "grass.dds")
{
	SB::Engine::GetSoundManager().Init("Audio/SoundBanks/Init.bnk");
	SB::Engine::GetSoundManager().LoadBank("Audio/SoundBanks/level1.bnk");

	CreateAndAddModel("models/stefan_sphere/testSpheres.fbx", SB::Vector3f(0.f, 0.f, 15.f));
	
	PushCameraController(std::make_shared<SB::FreeSpaceCameraController>(5.f, 1.5f));

	SB::Engine::GetRenderer().GetModelRenderer().SetAmbient(.05f);
	SB::Engine::GetRenderer().GetModelRenderer().SetDirectionalLight(0, SB::Vector3f(1.f, -1.f, 1.f), SB::Vector4f(1.0f, 1.0f, 1.0f, 1.f));
}

PbrTestScene::~PbrTestScene()
{
}

void PbrTestScene::Update(const SB::Time & aDeltaTime)
{
	SB::Engine::GetSoundManager().Update();

	if (ImGui::Begin("PBR Test Scene", nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse))
	{
		ImGui::Text("Move camera with WASD, QE, Ctrl, Space and Arrow Keys.");
	}
	ImGui::End();

	//myHead->SetMatrix(Matrix44f::CreateRotateAroundY(myTime.InSeconds()) * Matrix44f::CreateTranslation(0.f, 0.f, -5.f));

	SB::Scene::Update(aDeltaTime);
}

void PbrTestScene::Render()
{
	SB::Scene::Render();
}
