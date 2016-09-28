#pragma once

class PointLightModel;

class LightLoader
{
public:
	LightLoader();
	~LightLoader();
	std::shared_ptr<PointLightModel> LoadPointLightModel(const char* aPointLight);
private:
	std::shared_ptr<PointLightModel> CreatePointLightModel(const char* aPointLight);
	std::unordered_map<const char*, std::shared_ptr<PointLightModel>> myModels;
};

