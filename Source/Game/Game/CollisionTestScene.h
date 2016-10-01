#pragma once
#include "Engine\Scene\Scene.h"

namespace SB
{
	struct SplashScreenCBuffer;
	class SplashScreenEffect;
	class SphereCollider;
}

class CollisionTestScene : public SB::Scene
{
public:
	CollisionTestScene();
	virtual ~CollisionTestScene();
	
	virtual void Update(const SB::Time & aDeltaTime) override;

	virtual void Render() override;

private:

	std::unique_ptr<SB::SphereCollider> myCollisionSphere1;
	std::unique_ptr<SB::SphereCollider> myCollisionSphere2;

	std::shared_ptr<SB::GameObject> myTestObject1;
	std::shared_ptr<SB::GameObject> myTestObject2;

	void CreateFactories();
};

