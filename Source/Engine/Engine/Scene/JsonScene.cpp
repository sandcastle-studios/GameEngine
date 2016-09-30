#include "stdafx.h"
#include "JsonScene.h"
#include <Engine\Component\Factory\ComponentFactory.h>
#include <Engine\Model\ModelInstance.h>
#include <Engine\Component\ModelComponent.h>
#include <Engine\Component\LightComponent.h>
#include <Engine\GameObject\GameObject.h>
#include <Engine\Model\AssimpModel.h>
#include <Engine\Effect\StandardEffect.h>
#include <Engine\Camera\Camera.h>
#include <Engine\DataParser\DataParser.h>
#include <Engine\Camera\Controllers\FreeSpaceCameraController.h>
#include <Engine\Component\BouncingComponent.h>
#include "..\SoundManager\SoundManger.h"
#include "..\Game\ShotComponent.h"
#include "..\Utilities\Utilities\Intersection\IntersectionShapes\SphereIntersection.h"
#include "..\Utilities\Utilities\Intersection\IntersectionTests.h"

JsonScene::JsonScene(const char* aFilePath) : Scene(aFilePath, "grass.dds")
{
	PushCameraController(std::make_shared<FreeSpaceCameraController>(10.f, 3.f));
	SetCameraOrientation(Vector3f(0.f, 0.f, -15.f));
	mySprite.SetTexture(Engine::GetResourceManager().Get<Texture>("textures/cockpitPlaceholder.dds"));

	Engine::GetSoundManager().LoadBank("Audio/SoundBanks/level1.bnk");
	myEnemy = CreateAndAddModel("Assets/Models/Ships/Enemies/InterceptorX101/interceptorX101.fbx", Vector3f(0.f, 0.f, 5.f), Vector3f::One / 100.f);

	auto && movementComponent = GetComponentFactory<BouncingComponent>()->CreateComponent();
	myEnemy->AddComponent(movementComponent);
	myEnemy->SetPosition(Vector3f(0.f, 0.f, 0.f));

	myObjects.Add(myEnemy);

	myEnemy = CreateAndAddModel("Assets/Models/Ships/Enemies/InterceptorX101/interceptorX101.fbx", Vector3f(-40.f, 0.f, -5.f), Vector3f::One / 100.f);

	movementComponent = GetComponentFactory<BouncingComponent>()->CreateComponent();
	myEnemy->AddComponent(movementComponent);

	myObjects.Add(myEnemy);
}


JsonScene::~JsonScene()
{
}

void JsonScene::Update(const Time & aDeltaTime)
{
	GrowingArray<GameObject*>tempShoots;
	GrowingArray<GameObject*>NotShots;

	SphereIntersection tempEnemyCollider;
	SphereIntersection tempProjectileCollider;

	GetComponentFactory<ShotComponent>()->EnumerateActiveComponents(
		[&](ShotComponent & ashot)
		{
			tempShoots.Add(&ashot.GetGameObject());
		}
	);

	GetComponentFactory<ModelComponent>()->EnumerateActiveComponents(
		[&](ModelComponent & aThing)
		{
			if (aThing.GetGameObject().GetComponentCount<ShotComponent>() < 1)
			{
				NotShots.Add(&aThing.GetGameObject());
			}
		}
	);

	size_t c = 0;

	for (unsigned short iNotShot = 0; iNotShot < NotShots.Size(); ++iNotShot)
	{
		tempEnemyCollider.UpdatePosition(NotShots[iNotShot]->GetPosition());

		if (NotShots[iNotShot]->GetComponent<ModelComponent>() != nullptr)
		{
			c++;
			tempEnemyCollider.SetRadius((NotShots[iNotShot]->GetComponent<ModelComponent>()->GetBoundingBox().GetSize().z / 2.f) * NotShots[iNotShot]->GetScale().x);	
		}
		else
		{
			continue;
		}

		for (unsigned short iShot = 0; iShot < tempShoots.Size(); ++iShot)
		{
			GameObject & tempShoot = *tempShoots[iShot];

			tempProjectileCollider.UpdatePosition(tempShoot.GetPosition());
			tempProjectileCollider.SetRadius((tempShoot.GetComponent<ModelComponent>()->GetBoundingBox().GetSize().z / 2.f) * tempShoot.GetScale().x);

			if (Intersection::SphereVsSphere(tempEnemyCollider, tempProjectileCollider) == true)
			{
				if (tempShoot.GetComponent < ShotComponent>()->myHasHit == false)
				{
					tempShoot.GetComponent < ShotComponent>()->myHasHit = true;

					Engine::GetLogger().LogInfo("{0}", NotShots[iNotShot]->GetIdentifier());
					
					NotShots[iNotShot]->SetScale(NotShots[iNotShot]->GetScale() * Vector3f(1.01f, 1.01f, 1.01f));
				}
			}
		}
	}

	// Engine::GetLogger().LogInfo("{0}", c);

	Engine::GetSoundManager().Update();

	Scene::Update(aDeltaTime);
}

void JsonScene::Render()
{
	Scene::Render();

	Engine::GetRenderer().GetModelRenderer().RenderBuffer();

	Vector2f pos = Engine::GetRenderer().GetRenderTargetResolution() / 2.f;
	pos.x = std::floorf(pos.x);
	pos.y = std::floorf(pos.y);
	mySprite.SetOrigin(pos);
	mySprite.SetPosition(pos);
	mySprite.SetRotation(0.f);
	mySprite.SetScale(Engine::GetRenderer().GetRenderTargetResolution() / Vector2f(1920.f, 1080.f));
	mySprite.Render();
}


//PRIVATE FUNCTIONS:

