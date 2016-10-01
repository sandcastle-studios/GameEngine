#pragma once
#include <Engine\Scene\Scene.h>

class LightingTestScene : public SB::Scene
{
public:
	LightingTestScene();
	~LightingTestScene();
	
	virtual void Update(const SB::Time & aDeltaTime) override;
	virtual void Render() override;

private:
	std::shared_ptr<SB::ModelInstance> myHead;
};
