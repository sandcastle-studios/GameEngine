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
		aCamera.GetRototation().RotateZ(-aDeltaTime.InSeconds());
	}
	if (myRollRight)
	{
		aCamera.GetRototation().RotateZ(aDeltaTime.InSeconds());
	}

	const float speed = 1.f;

	if (myMoveLeft)
	{
		aCamera.AddPosition(aCamera.GetRototation().GetLeft() * speed * aDeltaTime.InSeconds());
	}
	if (myMoveRight)
	{
		aCamera.AddPosition(aCamera.GetRototation().GetRight() * speed * aDeltaTime.InSeconds());
	}

	if (myMoveForward)
	{
		aCamera.AddPosition(aCamera.GetRototation().GetForward() * speed * aDeltaTime.InSeconds());
	}
	if (myMoveBackward)
	{
		aCamera.AddPosition(aCamera.GetRototation().GetBackward() * speed * aDeltaTime.InSeconds());
	}

	if (myMoveUp)
	{
		aCamera.AddPosition(aCamera.GetRototation().GetUpward() * speed * aDeltaTime.InSeconds());
	}
	if (myMoveDown)
	{
		aCamera.AddPosition(aCamera.GetRototation().GetDownward() * speed * aDeltaTime.InSeconds());
	}

	const float rotateSpeed = 1.f;

	if (myPitchForward)
	{
		aCamera.GetRototation().RotateX(rotateSpeed * aDeltaTime.InSeconds());
	}
	if (myPitchBackward)
	{
		aCamera.GetRototation().RotateX(-rotateSpeed * aDeltaTime.InSeconds());
	}
	if (myRotateLeft)
	{
		aCamera.GetRototation().RotateY(rotateSpeed * aDeltaTime.InSeconds());
	}
	if (myRotateRight)
	{
		aCamera.GetRototation().RotateY(-rotateSpeed * aDeltaTime.InSeconds());
	}
}

ReceiveResult FreeSpaceCameraController::Receive(const AnyKeyDownMessage & aMessage)
{

}

ReceiveResult FreeSpaceCameraController::Receive(const AnyKeyUpMessage & aMessage)
{

}
