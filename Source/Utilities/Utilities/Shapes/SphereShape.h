#pragma once
#include "Utilities\Math\Vector3.h"


struct SphereShape
{
	SphereShape() : myPosition(Vector3f::One), Radius(1.f)
	{}

	Vector3f myPosition;
	float Radius;
};