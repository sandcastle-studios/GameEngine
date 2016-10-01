#include "stdafx.h"
#include "IntersectionTests.h"
#include "Utilities\Intersection\Colliders\SphereCollider.h"

namespace ENGINE_NAMESPACE
{

	namespace Intersection
	{
		bool SphereVsSphere(const SphereCollider & aFirstSphere, const SphereCollider & aSecondSphere)
		{
			Vector3f tempLengthDifference = aFirstSphere.GetPosition() - aSecondSphere.GetPosition();
			float tempCombinedRadius = aFirstSphere.GetRadius() + aSecondSphere.GetRadius();
			float tempDistance = tempLengthDifference.Length();

			if (tempDistance < tempCombinedRadius)
			{
				return true;
			}

			return false;
		}
	}

}