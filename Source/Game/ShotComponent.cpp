#include "stdafx.h"
#include "ShotComponent.h"
#include "..\Engine\Engine\GameObject\GameObject.h"

void ShotComponent::SetSpeed(const Vector3f & aSpeed)
{
	mySpeed = aSpeed;
}

void ShotComponent::Construct()
{
		
}

void ShotComponent::Destruct()
{

}

void ShotComponent::Update(const Time & aDeltaTime)
{
	myObject->SetPosition(myObject->GetPosition() + mySpeed * aDeltaTime.InSeconds());
}
