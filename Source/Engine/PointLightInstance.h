#pragma once


class PointLightModel;

class PointLightInstance
{
public:
	PointLightInstance();
	PointLightInstance(const Vector3f& aPosition, std::shared_ptr<PointLightModel> aPointLightModel);
	~PointLightInstance();
	const Vector3f& GetColor() const;
	const Vector3f& GetPosition() const;
	float GetIntensity() const;
	float GetRange() const;
	inline void SetPosition(const Vector3f& aPosition)
	{
		myPosition = aPosition;
	}
private:
	Vector3f myPosition;
	std::shared_ptr<PointLightModel> myModel;
};

