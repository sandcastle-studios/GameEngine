#include "stdafx.h"
#include "BouncingComponent.h"
#include "Engine/GameObject/GameObject.h"

BouncingComponent::BouncingComponent()
{
	const float velocityMagic = 3.f;
	myVelocity = Vector3f(velocityMagic, velocityMagic, velocityMagic);
	myMovingTowardsPoint = Vector3f(0.f, 0.f, 40.f);
	myThrowingAwayVelocity = Vector3f(0.f, 0.f, 0.f);
	myPointGravity = 0.0098f;
}

BouncingComponent::~BouncingComponent()
{
}

void BouncingComponent::Update(const Time & aDeltaTime)
{
	MoveObject(aDeltaTime);
}

void BouncingComponent::Render() const
{
	
}

void BouncingComponent::Construct()
{

}

void BouncingComponent::Destruct()
{

}

void BouncingComponent::MoveObject(const Time & aDeltaTime)
{
	const float warpRangeTest = 3.5f;
	//---------------------------- 
	if (myObject->GetPosition().x <= myMovingTowardsPoint.x + warpRangeTest &&
		myObject->GetPosition().x >= myMovingTowardsPoint.x - warpRangeTest &&
		myObject->GetPosition().y <= myMovingTowardsPoint.y + warpRangeTest &&
		myObject->GetPosition().y >= myMovingTowardsPoint.y - warpRangeTest &&
		myObject->GetPosition().z <= myMovingTowardsPoint.z + warpRangeTest &&
		myObject->GetPosition().z >= myMovingTowardsPoint.z - warpRangeTest)
	{
		const float range = 0.2f;
		float xVel = myRandomizer.GetRandomValue(-range, range);
		float yVel = myRandomizer.GetRandomValue(-range, range);
		float zVel = myRandomizer.GetRandomValue(-range, range);

		myThrowingAwayVelocity = Vector3f(xVel, yVel, zVel);
		myVelocity += myThrowingAwayVelocity;
	}
	//---------------------------- -

	Vector3f towardsPoint = myMovingTowardsPoint - myObject->GetPosition();
	towardsPoint.Normalize();
	towardsPoint *= myPointGravity;

	myVelocity += towardsPoint;

	Vector3f newPosition = myObject->GetPosition() + (myVelocity * aDeltaTime.InSeconds());

	myObject->SetPosition(newPosition);
}

//void BouncingComponent::Construct()
//{
//	throw std::logic_error("The method or operation is not implemented.");
//}
//
//void BouncingComponent::Destruct()
//{
//	throw std::logic_error("The method or operation is not implemented.");
//}
