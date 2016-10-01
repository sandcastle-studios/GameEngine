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
	myModel = std::make_shared<SB::CubeModel>(nullptr);

	myKeySubscription = std::make_shared<SB::Subscription<SB::KeyDownMessage<SB::KeyboardKey::eReturn>>>(
		[this] (const SB::KeyDownMessage<SB::KeyboardKey::eReturn> & aMessage) -> SB::ReceiveResult
		{
			return this->Receive(aMessage);
		}
	);
	myKeyUpSubscription = std::make_shared<SB::Subscription<SB::KeyUpMessage<SB::KeyboardKey::eReturn>>>(
		[this](const SB::KeyUpMessage<SB::KeyboardKey::eReturn> & aMessage) -> SB::ReceiveResult
	{
		return this->Receive(aMessage);
	}
	);

	myShooting = false;
	myShotCounter = 0;
	myShootTimer = 0.f;
}

void PlayerShootComponent::Destruct()
{
	myModel = nullptr;
	myKeySubscription = nullptr;
	myKeyUpSubscription = nullptr;
}

SB::ReceiveResult PlayerShootComponent::Receive(const SB::KeyDownMessage<SB::KeyboardKey::eReturn> & aMessage)
{
	myShooting = true;
	return SB::ReceiveResult::eContinue;
}

SB::ReceiveResult PlayerShootComponent::Receive(const SB::KeyUpMessage<SB::KeyboardKey::eReturn> & aMessage)
{
	myShooting = false;
	return SB::ReceiveResult::eContinue;
}

void PlayerShootComponent::Update(const SB::Time & aDeltaTime)
{
	myObject->SetPosition(myObject->GetScene().GetCamera().GetPosition());

	if (myShooting)
	{
		myShootTimer += aDeltaTime;
		
		while (myShootTimer >= 0.2f)
		{
			const SB::Camera & camera = myObject->GetScene().GetCamera();
			const SB::Vector3f right = camera.GetOrientation().GetRight();
			const float distance = 0.35f;

			myShotCounter++;
			std::shared_ptr<SB::GameObject> shot;

			const SB::Vector3f shotSize(0.1f, 0.1f, 1.5f);

			if (myShotCounter % 2 == 0)
				shot = myObject->GetScene().CreateObjectWithModel(myModel, camera.GetPosition() + right * distance, shotSize, camera.GetOrientation());
			else
				shot = myObject->GetScene().CreateObjectWithModel(myModel, camera.GetPosition() + right * -distance, shotSize, camera.GetOrientation());

			SB::Engine::GetSoundManager().PostEvent("Play_Derp");

			auto shotComponent = myObject->GetScene().GetComponentFactory<ShotComponent>()->CreateComponent();
			shotComponent->SetSpeed(camera.GetOrientation().GetForward() * 100.f);
			shot->AddComponent(shotComponent);
			myShootTimer -= 0.2f;
		}
	}
	else
	{
		myShootTimer = 0.2f;
	}
}
