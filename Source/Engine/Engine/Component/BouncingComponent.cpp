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

	Vector3f rot = myVelocity.GetNormalized();
	Quaternion orientation(rot.x, rot.y, rot.z, 1.f);

	myObject->SetRotation(orientation);



	/////////TEST FOR ENEMY ROTATION, WORKS FOR X AND Y AXIS BUT NOT WITH Z, BECAUSE REASONS///////////////////////////////////////
	//Vector3f baseDirection = Vector3f(0.f, 0.f, -1.f); //Forward vector of an Identity matrix. -1 because something is wrong with our shit
	//
	//Vector3f towardsPoint = myMovingTowardsPoint - myObject->GetPosition();
	//Vector3f nonNormalizedTowardsPoint = towardsPoint; //Can't check for length when normalized.
	//towardsPoint.Normalize();
	//
	//Vector3f newPosition = myObject->GetPosition() + (towardsPoint * aDeltaTime.InSeconds() * 5.f);
	//myObject->SetPosition(newPosition);
	//
	//Vector3f rotAxis = Vector3f::Cross(baseDirection, towardsPoint);
	//
	//float rotAngle = acosf(Vector3f::Dot(baseDirection, towardsPoint));
	//
	//Quaternion myOrientation;
	//myOrientation.RotateAlongAxis(rotAxis, rotAngle);
	//
	//myObject->SetRotation(myOrientation);
	//
	//if (nonNormalizedTowardsPoint.Length() <= 1.f)
	//{
	//	myMovingTowardsPoint.x = myRandomizer.GetRandomValue(-20, 20);
	//	myMovingTowardsPoint.y = myRandomizer.GetRandomValue(-20, 20);
	//}
	/////////TEST FOR ENEMY ROTATION, WORKS FOR X AND Y AXIS BUT NOT WITH Z, BECAUSE REASONS///////////////////////////////////////


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
