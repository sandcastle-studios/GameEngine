#pragma once
#include <Scene.h>
#include "LightData.h"

template<typename TDataType>
class ConstantBuffer;
class PointLightInstance;
class CubeTexture;


class LightingTestScene : public Scene
{
public:
	LightingTestScene(const char* aSkyBoxPath);
	~LightingTestScene();

	virtual void Render() override;


	virtual void Update(const Time & aDeltaTime) override;

private:
	std::unique_ptr<ConstantBuffer<LightData>> myConstantBuffer;
	std::shared_ptr<ModelInstance> myInstance;
	std::shared_ptr<CubeTexture> myCubeTexture;
	std::vector <std::shared_ptr<PointLightInstance>> myPointLightInstances;
};
