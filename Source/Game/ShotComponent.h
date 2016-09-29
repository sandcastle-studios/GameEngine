#pragma once
#include "Engine\Component\BaseComponent.h"
class ShotComponent : public BaseComponent
{
public:

	void SetSpeed(const Vector3f & aSpeed);

	virtual void Construct() override;


	virtual void Destruct() override;


	virtual void Update(const Time & aDeltaTime) override;

private:
	Vector3f mySpeed;
	Time myAge;
};

