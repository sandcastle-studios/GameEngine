#pragma once
#include "Engine\Component\BaseComponent.h"
class ShotComponent : public BaseComponent
{
public:

	void SetSpeed(const Vector3f & aSpeed);

	virtual void Construct() override;


	virtual void Destruct() override;

private:
	Vector3f mySpeed;
};

