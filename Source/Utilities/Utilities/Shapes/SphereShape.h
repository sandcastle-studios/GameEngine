#pragma once
#include "Utilities\Math\Vector3.h"

namespace ENGINE_NAMESPACE
{

	struct SphereShape
	{
		SphereShape(const Vector3f & aPosition, const float aRadius) : myPosition(aPosition), myRadius(aRadius)
		{}
		SphereShape() : myPosition(Vector3f::One), myRadius(1.f)
		{}

		Vector3f myPosition;
		float myRadius;
	};

}
