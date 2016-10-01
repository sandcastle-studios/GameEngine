#include "stdafx.h"
#include "CollisionManager.h"
#include "IntersectionTests.h"


namespace ENGINE_NAMESPACE
{
	CollisionManager::CollisionManager()
	{
	}


	CollisionManager::~CollisionManager()
	{
	}

	void CollisionManager::AddCollider(const CollisionCollider & aColliderToAdd)
	{
		myColliders.Add(&aColliderToAdd);
	}

	void CollisionManager::CheckCollisions()
	{
		for (unsigned short iCollider = 0; iCollider < myColliders.Size(); ++iCollider)
		{
			for (unsigned short iOtherCollider = iCollider + 1; iOtherCollider < myColliders.Size(); ++iOtherCollider)
			{
				CheckCollision(*myColliders[iCollider], *myColliders[iOtherCollider]);
			}
		}
	}

	bool CollisionManager::CheckCollision(const CollisionCollider & aFirstColliderToCheck, const CollisionCollider & aColliderToCheckAgainst)
	{
		if (Intersection::SphereVsSphere(aFirstColliderToCheck, aColliderToCheckAgainst) == true)
		{
			// do collision
			return true;
		}

		return false;
	}

}
