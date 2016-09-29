#include "stdafx.h"
#include "FreeSpaceCameraController.h"

FreeSpaceCameraController::FreeSpaceCameraController(const float aMovementSpeed, const float aRotationSpeed)
{
	myMovementSpeed = aMovementSpeed;
	myRotationSpeed = aRotationSpeed;

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
}

FreeSpaceCameraController::~FreeSpaceCameraController()
{
}

CameraControllerResult FreeSpaceCameraController::Update(const Time & aDeltaTime, Camera & aCamera)
{
	if (myRollLeft)
	{
		aCamera.GetOrientation().RotateZ(-aDeltaTime.InSeconds());
	}
	if (myRollRight)
	{
		aCamera.GetOrientation().RotateZ(aDeltaTime.InSeconds());
	}

	if (myMoveLeft)
	{
		aCamera.AddPosition(aCamera.GetOrientation().GetLeft() * myMovementSpeed * aDeltaTime.InSeconds());
	}
	if (myMoveRight)
	{
		aCamera.AddPosition(aCamera.GetOrientation().GetRight() * myMovementSpeed * aDeltaTime.InSeconds());
	}

	if (myMoveForward)
	{
		aCamera.AddPosition(aCamera.GetOrientation().GetForward() * myMovementSpeed * aDeltaTime.InSeconds());
	}
	if (myMoveBackward)
	{
		aCamera.AddPosition(aCamera.GetOrientation().GetBackward() * myMovementSpeed * aDeltaTime.InSeconds());
	}

	if (myMoveUp)
	{
		aCamera.AddPosition(aCamera.GetOrientation().GetUpward() * myMovementSpeed * aDeltaTime.InSeconds());
	}
	if (myMoveDown)
	{
		aCamera.AddPosition(aCamera.GetOrientation().GetDownward() * myMovementSpeed * aDeltaTime.InSeconds());
	}

	if (myPitchForward)
	{
		aCamera.GetOrientation().RotateX(myRotationSpeed * aDeltaTime.InSeconds());
	}
	if (myPitchBackward)
	{
		aCamera.GetOrientation().RotateX(-myRotationSpeed * aDeltaTime.InSeconds());
	}
	if (myRotateLeft)
	{
		aCamera.GetOrientation().RotateY(myRotationSpeed * aDeltaTime.InSeconds());
	}
	if (myRotateRight)
	{
		aCamera.GetOrientation().RotateY(-myRotationSpeed * aDeltaTime.InSeconds());
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
	}
	return ReceiveResult::eContinue;
}
