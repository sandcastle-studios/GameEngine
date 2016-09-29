#pragma once
#include "Engine/Component/BaseComponent.h"
#include <Utilities/Randomizer/Randomizer.h>

class BouncingComponent :
	public BaseComponent
{
public:
	BouncingComponent();
	~BouncingComponent();


	virtual void Update(const Time & aDeltaTime) override;

	virtual void Render() const override;

	virtual void Construct() override;

	virtual void Destruct() override;

private:
	void MoveObject(const Time & aDeltaTime);
	Randomizer myRandomizer;
	Vector3f myMovingTowardsPoint;
	Vector3f myVelocity;
	Vector3f myThrowingAwayVelocity;
	float myPointGravity;
};

