#pragma once
#include <Engine\Scene\Scene.h>

class LightingTestScene : public Scene, public Subscriber<AnyKeyDownMessage>, public Subscriber<AnyKeyUpMessage>
{
public:
	LightingTestScene();

	void RandomizeLights();

	~LightingTestScene();
	
	virtual void Update(const Time & aDeltaTime) override;

	void CameraMovement(const Time &aDeltaTime);

	virtual void Render() override;

	ReceiveResult Receive(const AnyKeyDownMessage & aMessage) override;
	ReceiveResult Receive(const AnyKeyUpMessage & aMessage) override;

private:
	std::shared_ptr<ModelInstance> myHead;

	std::array<Vector2f, 8> myLightRotationAxises;

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

	int myLightCount;
	float myMinSpeed;
	float myMaxSpeed;
	float myDirectionalLightIntensity;
};
