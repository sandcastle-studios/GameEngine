#pragma once
#include <Scene.h>

class AsynchronousLoadingTestScene : public Scene
{
public:
	AsynchronousLoadingTestScene();
	~AsynchronousLoadingTestScene();

	void Update(const Time & aDeltaTime) override;
};

