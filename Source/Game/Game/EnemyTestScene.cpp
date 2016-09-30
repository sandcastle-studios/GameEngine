#include "stdafx.h"
#include "EnemyTestScene.h"
#include <Engine\Camera\Controllers\FreeSpaceCameraController.h>
#include <Engine\Component\BouncingComponent.h>
#include "PlayerShootComponent.h"
#include <Engine/GameObject/GameObject.h>
#include <Engine/SoundManager/SoundManger.h>
#include <Engine\Model\AssimpModel.h>
#include "Utilities\Intersection\Colliders\SphereCollider.h"
#include "ShotComponent.h"
#include "..\Utilities\Utilities\Intersection\IntersectionTests.h"
#include "Engine\Component\ModelComponent.h"
#include <Engine\BoundingBox.h>

EnemyTestScene::EnemyTestScene(const char* aName)
	: Scene("EnemyScene", "grass.dds")
{

	PushCameraController(std::make_shared<FreeSpaceCameraController>(5.f, 1.5f));
	//CreateAndAddModel("models/test/test2.fbx", Vector3f(0.f, 0.f, 5.f), Vector3f::One /** 0.05f*/);

	Engine::GetSoundManager().Init("Audio/SoundBanks/Init.bnk");
	Engine::GetSoundManager().LoadBank("Audio/SoundBanks/level1.bnk");


	myPlayer = CreateGameObject(nullptr);
	auto && shootComponent = GetComponentFactory<PlayerShootComponent>()->CreateComponent();
	myPlayer->AddComponent(shootComponent);

	//-------------

	myEnemy = CreateAndAddModel("models/test/test2.fbx", Vector3f(0.f, 0.f, 5.f), Vector3f::One * 1.5f);

	auto && movementComponent = GetComponentFactory<BouncingComponent>()->CreateComponent();
	myEnemy->AddComponent(movementComponent);
	myEnemy->SetPosition(Vector3f(0.f, 0.f, 50.f));
}

EnemyTestScene::~EnemyTestScene()
{
}

void EnemyTestScene::Update(const Time & aDeltaTime)
{
	Engine::GetSoundManager().Update();

	

	SphereCollider tempProjectileCollider;


	float enemySize = myEnemy->GetComponent<ModelComponent>()->GetBoundingBox().GetSize().x / 2.f * myEnemy->GetScale().x;

	

	SphereCollider tempEnemyCollider;
	tempEnemyCollider.SetRadius(enemySize);
	

	tempEnemyCollider.UpdatePosition(myEnemy->GetPosition());

	bool tempEnemyHit = false;

	bool EnemyHit = false;

	auto testLamba = [&](ShotComponent & aShot)
	{
		tempProjectileCollider.UpdatePosition(aShot.GetGameObject().GetPosition());
		tempProjectileCollider.SetRadius(aShot.GetGameObject().GetComponent<ModelComponent>()->GetBoundingBox().GetSize().x / 2.f * aShot.GetGameObject().GetScale().x);

		if ((Intersection::SphereVsSphere(tempEnemyCollider, tempProjectileCollider) == true) && aShot.myHasHit == false)
		{
			aShot.myHasHit = true;
			EnemyHit = true;
			Engine::GetLogger().LogInfo("ARARARARAR");
		}
	};

	

	GetComponentFactory<ShotComponent>()->EnumerateActiveComponents( testLamba );

	if (EnemyHit == true)
	{
		myEnemy->SetScale(myEnemy->GetScale() + Vector3f(0.1f, 0.1f, 0.1f));
	}

	Scene::Update(aDeltaTime);
}
void EnemyTestScene::Render()
{
	Scene::Render();
}
