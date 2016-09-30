#pragma once

class SphereCollider;

namespace Intersection
{
	bool SphereVsSphere(const SphereCollider & aFirstSphere, const SphereCollider & aSecondSphere);
}