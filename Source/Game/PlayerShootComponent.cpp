#include "stdafx.h"
#include "PlayerShootComponent.h"
#include "Engine/Scene/Scene.h"
#include "Engine/Camera/Camera.h"
#include "Engine/Model/CubeModel.h"
#include "Engine/Effect/StandardEffect.h"
#include "ShotComponent.h"
#include <Engine/Component/Factory/ComponentFactory.h>
#include <Engine/GameObject/GameObject.h>
#include "../Engine/Engine/SoundManager/SoundManger.h"

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
	const Camera & camera = myObject->GetScene().GetCamera();
	const Vector3f right = camera.GetOrientation().GetRight();
	const float distance = 0.35f;

	myShotCounter++;
	std::shared_ptr<GameObject> shot;

	const Vector3f shotSize(0.1f, 0.1f, 1.5f);

	if (myShotCounter % 2 == 0)
		shot = myObject->GetScene().CreateObjectWithModel(myModel, camera.GetPosition() + right * distance, shotSize, camera.GetOrientation());
	else
		shot = myObject->GetScene().CreateObjectWithModel(myModel, camera.GetPosition() + right * -distance, shotSize, camera.GetOrientation());

	Engine::GetSoundManager().PostEvent("Play_Derp");

	auto shotComponent = myObject->GetScene().GetComponentFactory<ShotComponent>()->CreateComponent();
	shotComponent->SetSpeed(camera.GetOrientation().GetForward() * 10.f);
	shot->AddComponent(shotComponent);
	return ReceiveResult::eContinue;
}
