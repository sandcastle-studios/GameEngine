#pragma once
#include "Engine\Scene\Scene.h"

struct SplashScreenCBuffer;
class SplashScreenEffect;

class ModelInstance; 

class CockpitTestScene : public SB::Scene
{
public:
	CockpitTestScene();
	~CockpitTestScene();


	virtual void Update(const SB::Time & aDeltaTime) override;


	virtual void Render() override;

private:
	SB::Sprite mySprite;

	std::shared_ptr<ModelInstance> myTestObject1;

	void CreateFactories();
};

