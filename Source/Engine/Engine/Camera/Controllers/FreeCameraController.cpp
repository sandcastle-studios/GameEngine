#include "stdafx.h"
#include "FreeSpaceCameraController.h"
#include <Engine\SoundManager\SoundManger.h>

FreeSpaceCameraController::FreeSpaceCameraController(const float aMovementSpeed, const float aRotationSpeed)
{
	myRotationAccelerationCap =  aRotationSpeed / 3.f;

	myDriftMovementSpeed = aMovementSpeed;
	myDriftRotationSpeed = aRotationSpeed - myRotationAccelerationCap;

	myCurrentMovementSpeed = aMovementSpeed;
	myCurrentRotationSpeed = aRotationSpeed;

	myBoostMovementSpeed = myDriftMovementSpeed * 7.5f;
	myBoostRotationSpeed = (aRotationSpeed / 2.f) - myRotationAccelerationCap;


	myRotateLeft = false;
	myRotateRight = false;
	myMoveLeft = false;
	myMoveRight = false;
	myMoveForward = false;
	myMoveBackward = false;

	myPitchForward = false;
	myPitchBackward = false;
	myRollLeft = false;
	myRollRight = false;
	myMoveDown = false;
	myMoveUp = false;

	myBoosting = false;
}

FreeSpaceCameraController::~FreeSpaceCameraController()
{
}

CameraControllerResult FreeSpaceCameraController::Update(const Time & aDeltaTime, Camera & aCamera)
{
	UpdateAcceleration(aDeltaTime);

	bool isMoving = false;

	if (myRollLeft)
	{
		aCamera.GetOrientation().RotateZ(-myDriftRotationSpeed * aDeltaTime.InSeconds());
		isMoving = true;
	}
	if (myRollRight)
	{
		aCamera.GetOrientation().RotateZ(myDriftRotationSpeed * aDeltaTime.InSeconds());
		isMoving = true;
	}

	if (myMoveLeft)
	{
		aCamera.AddPosition(aCamera.GetOrientation().GetLeft() * myCurrentMovementSpeed * aDeltaTime.InSeconds());
		isMoving = true;
	}
	if (myMoveRight)
	{
		aCamera.AddPosition(aCamera.GetOrientation().GetRight() * myCurrentMovementSpeed * aDeltaTime.InSeconds());
		isMoving = true;
	}

	if (myMoveForward)
	{
		aCamera.AddPosition(aCamera.GetOrientation().GetForward() * myCurrentMovementSpeed * aDeltaTime.InSeconds());
		isMoving = true;
	}
	if (myMoveBackward)
	{
		aCamera.AddPosition(aCamera.GetOrientation().GetBackward() * myCurrentMovementSpeed * aDeltaTime.InSeconds());
		isMoving = true;
	}

	if (myMoveUp)
	{
		aCamera.AddPosition(aCamera.GetOrientation().GetUpward() * myCurrentMovementSpeed * aDeltaTime.InSeconds());
		isMoving = true;
	}
	if (myMoveDown)
	{
		aCamera.AddPosition(aCamera.GetOrientation().GetDownward() * myCurrentMovementSpeed * aDeltaTime.InSeconds());
		isMoving = true;
	}

	if (myPitchForward)
	{
		aCamera.GetOrientation().RotateX(myCurrentRotationSpeed * aDeltaTime.InSeconds());
		isMoving = true;
	}
	if (myPitchBackward)
	{
		aCamera.GetOrientation().RotateX(-myCurrentRotationSpeed * aDeltaTime.InSeconds());
		isMoving = true;
	}
	if (myRotateLeft)
	{
		aCamera.GetOrientation().RotateY(myCurrentRotationSpeed * aDeltaTime.InSeconds());
		isMoving = true;
	}
	if (myRotateRight)
	{
		aCamera.GetOrientation().RotateY(-myCurrentRotationSpeed * aDeltaTime.InSeconds());
		isMoving = true;
	}

	if (isMoving)
	{
		Engine::GetSoundManager().PostEvent("Player_Thruster");
	}
	else
	{
		Engine::GetSoundManager().PostEvent("Stop_Thruster");
	}

	return CameraControllerResult::eKeepControl;
}

ReceiveResult FreeSpaceCameraController::Receive(const AnyKeyDownMessage & aMessage)
{
	switch (aMessage.key)
	{
	case KeyboardKey::eQ:
		myRollLeft = true;
		break;
	case KeyboardKey::eE:
		myRollRight = true;
		break;

	case KeyboardKey::eA:
		myMoveLeft = true;
		break;
	case KeyboardKey::eD:
		myMoveRight = true;
		break;
	case KeyboardKey::eW:
		myMoveForward = true;
		break;
	case KeyboardKey::eS:
		myMoveBackward = true;
		break;

	case KeyboardKey::eLeft:
		myRotateLeft = true;
		break;
	case KeyboardKey::eRight:
		myRotateRight = true;
		break;
	case KeyboardKey::eUp:
		myPitchForward = true;
		break;
	case KeyboardKey::eDown:
		myPitchBackward = true;
		break;

	case KeyboardKey::eControl:
		myMoveDown = true;
		break;
	case KeyboardKey::eSpace:
		myMoveUp = true;
		break;

	case KeyboardKey::eShift:
		SetIsBoosting(true);
		break;

	case KeyboardKey::eAlt:
		Engine::GetLogger().LogInfo("eAlt pressed");
		break;
	}
	return ReceiveResult::eContinue;
}

ReceiveResult FreeSpaceCameraController::Receive(const AnyKeyUpMessage & aMessage)
{
	switch (aMessage.key)
	{
	case KeyboardKey::eQ:
		myRollLeft = false;
		break;
	case KeyboardKey::eE:
		myRollRight = false;
		break;

	case KeyboardKey::eA:
		myMoveLeft = false;
		break;
	case KeyboardKey::eD:
		myMoveRight = false;
		break;
	case KeyboardKey::eW:
		myMoveForward = false;
		break;
	case KeyboardKey::eS:
		myMoveBackward = false;
		break;

	case KeyboardKey::eLeft:
		myRotateLeft = false;
		break;
	case KeyboardKey::eRight:
		myRotateRight = false;
		break;
	case KeyboardKey::eUp:
		myPitchForward = false;
		break;
	case KeyboardKey::eDown:
		myPitchBackward = false;
		break;

	case KeyboardKey::eControl:
		myMoveDown = false;
		break;
	case KeyboardKey::eSpace:
		myMoveUp = false;
		break;

	case KeyboardKey::eShift:
		SetIsBoosting(false);
		break;
	}
	return ReceiveResult::eContinue;
}


//PRIVATE FUNCTIONS:

void FreeSpaceCameraController::SetIsBoosting(const bool aIsBoosting)
{
	myBoosting = aIsBoosting;

	//Uncomment movement speed change below to disable gradual acceleration in favor of instant boost speed on/off
	if (aIsBoosting == true)
	{
		//myCurrentMovementSpeed = myBoostMovementSpeed;
		myCurrentRotationSpeed = myBoostRotationSpeed;
	}
	else
	{
		//myCurrentMovementSpeed = myDriftMovementSpeed;
		myCurrentRotationSpeed = myDriftRotationSpeed;
	}
}

void FreeSpaceCameraController::UpdateAcceleration(const Time & aDeltaTime)
{
	//Update movement acceleration
	const float AccelerationSpeed = (myBoostMovementSpeed - myDriftMovementSpeed) / 1.f;
	const float DecelerationSpeed = AccelerationSpeed * 2.f;

	if (myBoosting == true)
	{
		if (myCurrentMovementSpeed < myBoostMovementSpeed)
		{
			myCurrentMovementSpeed += AccelerationSpeed * aDeltaTime.InSeconds();

			if (myCurrentMovementSpeed > myBoostMovementSpeed)
				myCurrentMovementSpeed = myBoostMovementSpeed;
		}
	}
	else
	{
		if (myCurrentMovementSpeed > myDriftMovementSpeed)
		{
			myCurrentMovementSpeed -= DecelerationSpeed * aDeltaTime.InSeconds();

			if (myCurrentMovementSpeed < myDriftMovementSpeed)
				myCurrentMovementSpeed = myDriftMovementSpeed;
		}
	}


	//Update rotation acceleration
	float currentRotateSpeedCap = GetCurrentRotateAccelerationCap();
	float currentRotateSpeedBase = GetCurrentRotateAccelerationBase();
	const float RotateAccelerationSpeed = (currentRotateSpeedCap - currentRotateSpeedBase) / 1.f;
	if (GetIsRotating() == false)
	{
		myCurrentRotationSpeed = currentRotateSpeedBase;
		/*
		if (myCurrentRotationSpeed > currentRotateSpeedBase)
		{
		myCurrentRotationSpeed -= RotateAccelerationSpeed * aDeltaTime.InSeconds();
		if (myCurrentRotationSpeed < currentRotateSpeedBase)
		myCurrentRotationSpeed = currentRotateSpeedBase;
		}
		*/
	}
	else
	{		
		if (myCurrentRotationSpeed < currentRotateSpeedCap)
		{
			myCurrentRotationSpeed += RotateAccelerationSpeed * aDeltaTime.InSeconds();
			if (myCurrentRotationSpeed > currentRotateSpeedCap)
				myCurrentRotationSpeed = currentRotateSpeedCap;
		}
	}
}

bool FreeSpaceCameraController::GetIsMoving() const
{
	return (myMoveUp == true || myMoveDown == true || myMoveForward == true || myMoveBackward == true || myMoveLeft == true || myMoveRight == true);
}

bool FreeSpaceCameraController::GetIsRotating() const
{
	return (myRotateLeft == true || myRotateRight == true || myRollLeft == true || myRollRight == true || myPitchForward == true || myPitchBackward == true);
}

float FreeSpaceCameraController::GetCurrentRotateAccelerationCap() const
{
	if (myBoosting == false)
	{
		return myDriftRotationSpeed + myRotationAccelerationCap;
	}
	else
	{
		return myBoostRotationSpeed + myRotationAccelerationCap;
	}
}

float FreeSpaceCameraController::GetCurrentRotateAccelerationBase() const
{
	if (myBoosting == false)
	{
		return myDriftRotationSpeed;
	}
	else
	{
		return myBoostRotationSpeed;
	}
}
