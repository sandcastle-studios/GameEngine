#include "stdafx.h"
#include "ShotComponent.h"
#include <Engine\GameObject\GameObject.h>

void ShotComponent::SetSpeed(const SB::Vector3f & aSpeed)
{
	mySpeed = aSpeed;
	myHasHit = false;
}

void ShotComponent::Construct()
{
	myAge = 0.f;
	mySpeed = SB::Vector3f::Zero;
}

void ShotComponent::Destruct()
{
	// Engine::GetLogger().LogInfo("ShotComponent::Destruct");
}

void ShotComponent::Update(const SB::Time & aDeltaTime)
{
	myAge += aDeltaTime;

	if (myAge.InSeconds() >= 10.f)
	{
		// Engine::GetLogger().LogInfo("myAge{0}", myAge.InSeconds());
		myObject->Remove();
	}

	myObject->SetPosition(myObject->GetPosition() + mySpeed * aDeltaTime.InSeconds());
}
