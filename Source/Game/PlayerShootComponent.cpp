#include "stdafx.h"
#include "PlayerShootComponent.h"
#include "Engine/Scene/Scene.h"
#include "Engine/Camera/Camera.h"
#include "Engine/Model/CubeModel.h"
#include "Engine/Effect/StandardEffect.h"
#include "ShotComponent.h"
#include "../Engine/Engine/Component/Factory/ComponentFactory.h"
#include "../Engine/Engine/GameObject/GameObject.h"

void PlayerShootComponent::Construct()
{
	myModel = std::make_shared<CubeModel>(std::make_shared<StandardEffect>(), nullptr);

	myKeySubscription = std::make_shared<Subscription<KeyDownMessage<KeyboardKey::eReturn>>>(
		[this] (const KeyDownMessage<KeyboardKey::eReturn> & aMessage) -> ReceiveResult
		{
			return this->Receive(aMessage);
		}
	);

	myShotCounter = 0;
}

void PlayerShootComponent::Destruct()
{
	myModel = nullptr;
	myKeySubscription = nullptr;
}

ReceiveResult PlayerShootComponent::Receive(const KeyDownMessage<KeyboardKey::eReturn> & aMessage)
{
	const Camera & camera = myScene->GetCamera();
	const Vector3f right = camera.GetOrientation().GetRight();
	const float distance = 0.125f;

	myShotCounter++;
	std::shared_ptr<GameObject> shot;

	if (myShotCounter % 2 == 0)
		shot = myScene->CreateObjectWithModel(myModel, camera.GetPosition() + right * distance, Vector3f::One * 0.03f, camera.GetOrientation());
	else
		shot = myScene->CreateObjectWithModel(myModel, camera.GetPosition() + right * -distance, Vector3f::One * 0.03f, camera.GetOrientation());
	shot->AddComponent(myScene->GetComponentFactory<ShotComponent>()->CreateComponent());
	return ReceiveResult::eContinue;
}

void PlayerShootComponent::SetScene(Scene & aScene)
{
	myScene = &aScene;
}
