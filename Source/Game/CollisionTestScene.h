#pragma once
#include "Engine\Scene\Scene.h"


class CollisionTestScene :
	public Scene
{
public:
	CollisionTestScene();
	virtual ~CollisionTestScene();


	virtual void Update(const Time & aDeltaTime) override;


	virtual void Render() override;

private:
	void CreateFactories();
};

