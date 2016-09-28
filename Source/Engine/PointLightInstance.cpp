#include "stdafx.h"
#include "PointLightInstance.h"
#include "PointLightModel.h"

PointLightInstance::PointLightInstance()
{
	myModel = nullptr;
	myPosition = Vector3f::Zero;
}


PointLightInstance::PointLightInstance(const Vector3f& aPosition, std::shared_ptr<PointLightModel> aPointLightModel)
{
	myModel = aPointLightModel;
	myPosition = aPosition;
}

PointLightInstance::~PointLightInstance()
{
}

const Vector3f& PointLightInstance::GetColor() const
{
	return myModel->GetColor();
}
const Vector3f& PointLightInstance::GetPosition() const
{
	return myPosition;
}
float PointLightInstance::GetIntensity() const
{
	return myModel->GetIntensity();
}
float PointLightInstance::GetRange() const
{
	return myModel->GetRange();
}
