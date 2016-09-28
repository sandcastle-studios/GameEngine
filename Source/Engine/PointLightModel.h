#pragma once


class PointLightModel
{
public:
	PointLightModel();
	PointLightModel(const Vector3f& aColor, const float aIntensity, const float aRange);
	~PointLightModel();
	inline const Vector3f& GetColor() const 
	{ 
		return myColor; 
	}
	inline void SetColor(const Vector3f& aValue) 
	{ 
		myColor = aValue;
	}
	inline float GetIntensity() const
	{
		return myIntensity;
	}
	inline void SetIntensity(const float aValue)
	{
		myIntensity = aValue;
	}
	inline float GetRange() const
	{
		return myRange;
	}
	inline void SetRange(const float aValue)
	{
		myRange = aValue;
	}
private:
	friend class LightLoader;
	Vector3f myColor;
	float myIntensity;
	float myRange;
};

