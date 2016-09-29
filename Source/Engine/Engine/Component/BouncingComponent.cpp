#include "stdafx.h"
#include "BouncingComponent.h"
#include "Engine/GameObject/GameObject.h"

const float epsilonTest = 0.01f;

BouncingComponent::BouncingComponent()
{
	myVelocity.x = 3.f;
	myMovingTowardsPoint = Vector3f(0.f, 0.f, 30.f);
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
	if (myObject->GetPosition().x <= myMovingTowardsPoint.x + epsilonTest &&
		myObject->GetPosition().x >= myMovingTowardsPoint.x - epsilonTest &&
		myObject->GetPosition().y <= myMovingTowardsPoint.y + epsilonTest &&
		myObject->GetPosition().y >= myMovingTowardsPoint.y - epsilonTest &&
		myObject->GetPosition().z <= myMovingTowardsPoint.z + epsilonTest &&
		myObject->GetPosition().z >= myMovingTowardsPoint.z - epsilonTest)
	{
		const float range = 5.f;
		myThrowingAwayVelocity = Vector3f(myRandomizer.GetRandomValue(-range, range), myRandomizer.GetRandomValue(-range, range), myRandomizer.GetRandomValue(-range, range));
		myVelocity += myThrowingAwayVelocity;
	}
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
