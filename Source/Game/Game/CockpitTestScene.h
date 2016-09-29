#pragma once
#include "Engine\Scene\Scene.h"

struct SplashScreenCBuffer;
class SplashScreenEffect;

class ModelInstance; 

class CockpitTestScene : public Scene
{
public:
	CockpitTestScene();
	~CockpitTestScene();


	virtual void Update(const Time & aDeltaTime) override;


	virtual void Render() override;

private:
	Sprite mySprite;

	std::unique_ptr<ConstantBuffer<SplashScreenCBuffer>> myConstantBuffer;
	std::shared_ptr<SplashScreenEffect> mySplashScreenEffect;

	std::shared_ptr<ModelInstance> myTestObject1;

	void CreateFactories();
};

