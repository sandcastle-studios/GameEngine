#pragma once


namespace ENGINE_NAMESPACE
{
	class SphereCollider;

	typedef SphereCollider CollisionCollider;

	class CollisionManager
	{
	public:
		CollisionManager();
		~CollisionManager();

		void AddCollider(const CollisionCollider & aColliderToAdd);

		void CheckCollisions();

	private:
		bool CheckCollision(const CollisionCollider & aFirstColliderToCheck, const CollisionCollider & aColliderToCheckAgainst);

		GrowingArray<const CollisionCollider*> myColliders;
	};

}

