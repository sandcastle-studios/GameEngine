#include "stdafx.h"
#include "IntersectionTests.h"
#include "Utilities\Intersection\IntersectionShapes\SphereIntersection.h"

namespace Intersection
{
	bool SphereVsSphere(const SphereIntersection & aFirstSphere, const SphereIntersection & aSecondSphere)
	{
		Vector3f tempLengthDifference = aFirstSphere.GetPosition() - aSecondSphere.GetPosition();
		float tempCombinedRadius = aFirstSphere.GetRadiusSquared() + aSecondSphere.GetRadiusSquared();

		if (tempLengthDifference.Length2() < tempCombinedRadius)
		{
			return true;
		}

		return false;
	}
}