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
	GetCamera().SetPosition(Vector3f(0.0f, 0.0f, -1.0f));

	success = Engine::GetSoundManager().Init("Audio/SoundBanks/Init.bnk");
	Engine::GetSoundManager().SetErrorCallBack(ErrorCallback);

	success = Engine::GetSoundManager().LoadBank("Audio/SoundBanks/level1.bnk");
	success;
	Engine::GetSoundManager().PostEvent("Play_Derp");
	myPlaying = false;
}


SoundTestScene::~SoundTestScene()
{
}

void SoundTestScene::Update(const Time & aDeltaTime)
{
	if (mySoundLoop> 1.0f)
	{
		myPlaying = false;
		mySoundLoop = 0.0f;
	}
	if (!myPlaying)
	{
		Engine::GetSoundManager().PostEvent("Play_Derp");
		myPlaying = true;
	}
	Engine::GetSoundManager().Update();
	mySoundLoop += 0.0008f;



	//myObjects[0]->SetMatrix(myObjects[0]->GetMatrix()*Matrix44f::CreateRotateAroundY(0.7f * aDeltaTime.InSeconds()));
	Scene::Update(aDeltaTime);
}

void SoundTestScene::Render()
{
	Scene::Render();
}
