#include "stdafx.h"
#include "PlayerTestScene.h"
#include <Engine\Camera\Controllers\FreeSpaceCameraController.h>
#include "PlayerShootComponent.h"
#include <Engine/GameObject/GameObject.h>

PlayerTestScene::PlayerTestScene()
	: Scene("PlayerTestScene", "grass.dds")
{
	PushCameraController(std::make_shared<FreeSpaceCameraController>(5.f, 1.5f));
	CreateAndAddModel("models/pillar/pillarShortObelisk.fbx", Vector3f(0.f, 0.f, 5.f), Vector3f::One * 0.05f);

	myPlayer = std::make_shared<GameObject>();
	auto && shootComponent = GetComponentFactory<PlayerShootComponent>()->CreateComponent();
	shootComponent->SetScene(*this);
	myPlayer->AddComponent(shootComponent);
	myObjects.Add(myPlayer);
}

PlayerTestScene::~PlayerTestScene()
{
}
