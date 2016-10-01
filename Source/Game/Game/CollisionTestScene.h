#pragma once
#include "Engine\Scene\Scene.h"

struct SplashScreenCBuffer;
class SplashScreenEffect;

class SphereCollider;

class CollisionTestScene :
	public Scene
{
public:
	CollisionTestScene();
	virtual ~CollisionTestScene();


	virtual void Update(const Time & aDeltaTime) override;


	virtual void Render() override;

private:

	std::unique_ptr<SphereCollider> myCollisionSphere1;
	std::unique_ptr<SphereCollider> myCollisionSphere2;

	std::shared_ptr<GameObject> myTestObject1;
	std::shared_ptr<GameObject> myTestObject2;

	void CreateFactories();
};
