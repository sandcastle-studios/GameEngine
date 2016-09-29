#pragma once
#include "Engine\Scene\Scene.h"

struct SplashScreenCBuffer;
class SplashScreenEffect;

class SphereIntersection;

class CollisionTestScene :
	public Scene
{
public:
	CollisionTestScene();
	virtual ~CollisionTestScene();


	virtual void Update(const Time & aDeltaTime) override;


	virtual void Render() override;

private:
	std::unique_ptr<SphereIntersection> myCollisionSphere1;
	std::unique_ptr<SphereIntersection> myCollisionSphere2;

	std::shared_ptr<ModelInstance> myTestObject1;
	std::shared_ptr<ModelInstance> myTestObject2;

	void CreateFactories();
};

