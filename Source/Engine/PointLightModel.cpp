#include "stdafx.h"
#include "PointLightModel.h"


PointLightModel::PointLightModel()
{
	myColor = Vector3f::Zero;
	myIntensity = 0.f;
	myRange = 0.f;
}


PointLightModel::PointLightModel(const Vector3f& aColor, const float aIntensity, const float aRange)
{
	myColor = aColor;
	myIntensity = aIntensity;
	myRange = aRange;
}

PointLightModel::~PointLightModel()
{
}
