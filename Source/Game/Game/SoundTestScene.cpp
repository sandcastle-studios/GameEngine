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
	std::shared_ptr<AssimpModel> model = std::make_shared<AssimpModel>(myEffect, "models/Modelviewer_Exempelmodell/K11_1415.fbx");
	//myObjects.push_back(std::make_shared<ModelInstance>(model));
	//GetCamera().SetPosition(Vector3f(0.0f, 0.0f, -1.0f));

	success = Engine::GetSoundManager().Init("Audio/SoundBanks/Init.bnk");
	Engine::GetSoundManager().SetErrorCallBack(ErrorCallback);

	success = Engine::GetSoundManager().LoadBank("Audio/SoundBanks/level1.bnk");
	success;
	
	myPlaying = false;
}


SoundTestScene::~SoundTestScene()
{
}

void SoundTestScene::Update(const Time & aDeltaTime)
{
	if (ImGui::Begin("Sound stuffs", nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse))
	{
		if (ImGui::Button("Play sound!") == true)
		{
			PostMaster::Post(PlaySoundEvent("Play_Derp"));
		}
	}
	ImGui::End();


	Engine::GetSoundManager().Update();
	//myObjects[0]->SetMatrix(myObjects[0]->GetMatrix()*Matrix44f::CreateRotateAroundY(0.7f * aDeltaTime.InSeconds()));
	Scene::Update(aDeltaTime);
}

void SoundTestScene::Render()
{
	Scene::Render();
}
