#pragma once
#include <Scene.h>

class LightingTestScene : public Scene
{
public:
	LightingTestScene();
	~LightingTestScene();
	
	virtual void Update(const Time & aDeltaTime) override;
	virtual void Render() override;

private:
	std::shared_ptr<ModelInstance> myHead;
};
