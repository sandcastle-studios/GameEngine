#pragma once
#include "Engine\Camera\CameraController.h"

class FreeSpaceCameraController : public CameraController, public Subscriber<AnyKeyDownMessage>, public Subscriber<AnyKeyUpMessage>
{
public:
	FreeSpaceCameraController(const float aMovementSpeed, const float aRotationSpeed);
	~FreeSpaceCameraController();

	virtual CameraControllerResult Update(const Time & aDeltaTime, Camera & aCamera) override;

	ReceiveResult Receive(const AnyKeyUpMessage & aMessage) override;
	ReceiveResult Receive(const AnyKeyDownMessage & aMessage) override;

private:
	float myMovementSpeed;
	float myRotationSpeed;

	bool myRotateLeft;
	bool myRotateRight;
	bool myMoveLeft;
	bool myMoveRight;
	bool myMoveForward;
	bool myMoveBackward;

	bool myPitchForward;
	bool myPitchBackward;
	bool myRollLeft;
	bool myRollRight;
	bool myMoveDown;
	bool myMoveUp;
};
