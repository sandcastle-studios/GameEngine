#include "stdafx.h"
#include "ShotComponent.h"
#include "..\Engine\Engine\GameObject\GameObject.h"

void ShotComponent::SetSpeed(const Vector3f & aSpeed)
{
	mySpeed = aSpeed;
}

void ShotComponent::Construct()
{
	myAge = 0.f;
	mySpeed = Vector3f::Zero;
}

void ShotComponent::Destruct()
{
	Engine::GetLogger().LogInfo("ShotComponent::Destruct");
}

void ShotComponent::Update(const Time & aDeltaTime)
{
	myAge += aDeltaTime;

	if (myAge.InSeconds() >= 0.5f)
	{
		// Engine::GetLogger().LogInfo("myAge{0}", myAge.InSeconds());
		myObject->Remove();
	}

	myObject->SetPosition(myObject->GetPosition() + mySpeed * aDeltaTime.InSeconds());
}
