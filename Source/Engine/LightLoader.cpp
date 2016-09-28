#include "stdafx.h"
#include "LightLoader.h"
#include "PointLightModel.h"


LightLoader::LightLoader()
{
}


LightLoader::~LightLoader()
{
}

std::shared_ptr<PointLightModel> LightLoader::LoadPointLightModel(const char* aPointLight)
{
	if (myModels.find(aPointLight) == myModels.end())
	{
		return CreatePointLightModel(aPointLight);
	}
	return myModels[aPointLight];
}

std::shared_ptr<PointLightModel> LightLoader::CreatePointLightModel(const char* aPointLight)
{
	if (strcmp(aPointLight, "WhiteLight") == 0)
	{
		std::shared_ptr<PointLightModel> model = std::make_shared<PointLightModel>(Vector3f(1.f, 1.f, 1.f), 1.f, 5.f);
		myModels[aPointLight] = model;
	}
	else if (strcmp(aPointLight, "RedLight") == 0)
	{
		std::shared_ptr<PointLightModel> model = std::make_shared<PointLightModel>(Vector3f(1.f, 0.f, 0.f), 1.f, 5.f);
		myModels[aPointLight] = model;
	}
	else if (strcmp(aPointLight, "BlueLight") == 0)
	{
		std::shared_ptr<PointLightModel> model = std::make_shared<PointLightModel>(Vector3f(0.f, 0.f, 1.f), 1.f, 5.f);
		myModels[aPointLight] = model;
	}
	else if (strcmp(aPointLight, "GreenLight") == 0)
	{
		std::shared_ptr<PointLightModel> model = std::make_shared<PointLightModel>(Vector3f(0.f, 1.f, 0.f), 1.f, 5.f);
		myModels[aPointLight] = model;
	}
	else
	{
		assert(false && "FAILED TO CREATE POINTLIGHT!!!");
	}
	return myModels[aPointLight];
}
