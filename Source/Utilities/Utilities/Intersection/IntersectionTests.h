#pragma once

class SphereCollider;

namespace ENGINE_NAMESPACE
{

	namespace Intersection
	{
		bool SphereVsSphere(const SphereCollider & aFirstSphere, const SphereCollider & aSecondSphere);
	}

}