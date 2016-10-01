#pragma once

class SphereIntersection;

namespace ENGINE_NAMESPACE
{

	namespace Intersection
	{
		bool SphereVsSphere(const SphereIntersection & aFirstSphere, const SphereIntersection & aSecondSphere);
	}

}