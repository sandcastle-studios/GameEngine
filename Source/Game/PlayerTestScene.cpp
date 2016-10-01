#include "stdafx.h"
#include "PlayerTestScene.h"
#include <Engine\Camera\Controllers\FreeSpaceCameraController.h>
#include "PlayerShootComponent.h"
#include <Engine/GameObject/GameObject.h>
#include <Engine/SoundManager/SoundManger.h>

PlayerTestScene::PlayerTestScene()
	: Scene("PlayerTestScene", "grass.dds")
{

	PushCameraController(std::make_shared<SB::FreeSpaceCameraController>(5.f, 1.5f));
	// CreateAndAddModel("models/pillar/pillarShortObelisk.fbx", Vector3f(0.f, 0.f, 5.f), Vector3f::One * 0.05f);

	SB::Engine::GetSoundManager().LoadBank("Audio/SoundBanks/level1.bnk");

	myPlayer = CreateGameObject();
	auto && shootComponent = GetComponentFactory<PlayerShootComponent>()->CreateComponent();
	myPlayer->AddComponent(shootComponent);
}

PlayerTestScene::~PlayerTestScene()
{
}

void PlayerTestScene::Update(const SB::Time & aDeltaTime)
{
	SB::Engine::GetSoundManager().Update();
	SB::Scene::Update(aDeltaTime);
}
void PlayerTestScene::Render()
{
	SB::Scene::Render();
}
