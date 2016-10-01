#include "stdafx.h"
#include "SoundTestScene.h"
#include "..\Engine\Engine\Model\AssimpModel.h"
#include "Engine\Effect\StandardEffect.h"
#include <Engine\Model\ModelInstance.h>
#include <Engine\Camera\Camera.h>
#include <Engine\Rendering\DXRenderer.h>
#include <Engine\Rendering\ModelRenderer.h>
#include "Engine\Engine.h"
#include "Engine\SoundManager\SoundManger.h"
#include "..\Engine\Engine\Camera\Controllers\FreeSpaceCameraController.h"
#include "..\ImGui\imgui.h"
#include "..\Engine\Engine\SoundManager\PlaySoundEvent.h"


void ErrorCallback(const char* aError)
{
	std::string temp = aError;
	std::wstring errorMsg(temp.begin(), temp.end());
	OutputDebugString(errorMsg.c_str());
}

SoundTestScene::SoundTestScene()
{
	bool success;
	std::shared_ptr<SB::AssimpModel> model = std::make_shared<SB::AssimpModel>("models/Modelviewer_Exempelmodell/K11_1415.fbx");
	//myObjects.push_back(std::make_shared<ModelInstance>(model));
	SetCameraOrientation(SB::Vector3f(0.0f, 0.0f, -1.0f));

	PushCameraController(std::make_shared<SB::FreeSpaceCameraController>(5.f, 1.5f));

	success = SB::Engine::GetSoundManager().LoadBank("Audio/SoundBanks/level1.bnk");
	success;
	myPlaying = false;
}


SoundTestScene::~SoundTestScene()
{
}

void SoundTestScene::Update(const SB::Time & aDeltaTime)
{
	if (ImGui::Begin("Sound stuffs", nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse))
	{
		if (ImGui::Button("Play sound!") == true)
		{
			SB::PostMaster::Post(SB::PlaySoundEvent("Play_Derp"));
		}
	}
	ImGui::End();


	SB::Engine::GetSoundManager().Update();
	//myObjects[0]->SetMatrix(myObjects[0]->GetMatrix()*Matrix44f::CreateRotateAroundY(0.7f * aDeltaTime.InSeconds()));
	SB::Scene::Update(aDeltaTime);
}

void SoundTestScene::Render()
{
	SB::Scene::Render();
}
