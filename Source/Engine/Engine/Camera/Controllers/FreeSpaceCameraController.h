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
	void SetIsBoosting(const bool aIsBoosting);
	void UpdateAcceleration(const Time & aDeltaTime);

	float myCurrentMovementSpeed;
	float myCurrentRotationSpeed;
	float myDriftMovementSpeed;
	float myDriftRotationSpeed;
	float myBoostMovementSpeed;
	float myBoostRotationSpeed;

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

	bool myBoosting;
};
