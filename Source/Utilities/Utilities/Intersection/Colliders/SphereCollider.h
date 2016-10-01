#pragma once

namespace ENGINE_NAMESPACE
{

	class SphereCollider
	{
	public:
		SphereCollider();
		SphereCollider(const SphereShape & aSphere) : myPosition(aSphere.myPosition)
		{
			SetRadius(aSphere.myRadius);
		}

		~SphereCollider();

		void SetSphere(const SphereShape & aSphere)
		{
			UpdatePosition(aSphere.myPosition);
			SetRadius(aSphere.myRadius);
		}

		void UpdatePosition(const Vector3f & aPosition)
		{
			myPosition = aPosition;
		}
		const Vector3f & GetPosition() const
		{
			return myPosition;
		}

		void SetRadius(const float aRadius)
		{
			myRadius = aRadius;
			myRadiusSquared = aRadius * aRadius;
		}
		float GetRadius() const
		{
			return myRadius;
		}
		float GetRadiusSquared() const
		{
			return myRadiusSquared;
		}

		SphereShape GetBasicSphere()
		{
			return SphereShape(myPosition, myRadius);
		}

	private:
		Vector3f myPosition;
		float myRadius;
		float myRadiusSquared;
	};


}

