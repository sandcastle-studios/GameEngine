#pragma once
class SphereIntersection
{
public:
	SphereIntersection();
	SphereIntersection(const SphereShape & aSphere) : myPosition(aSphere.myPosition)
	{
		SetRadius(aSphere.myRadius);
	}

	~SphereIntersection();

	void SetSphere(const SphereShape & aSphere)
	{
		SetPosition(aSphere.myPosition);
		SetRadius(aSphere.myRadius);
	}

	void SetPosition(const Vector3f & aPosition)
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

