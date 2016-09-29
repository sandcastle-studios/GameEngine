#pragma once
#include <Engine\Scene\Scene.h>

class PbrTestScene : public Scene
{
public:
	PbrTestScene();
	~PbrTestScene();

	virtual void Update(const Time & aDeltaTime) override;
	virtual void Render() override;

private:
	std::shared_ptr<ModelInstance> myHead;
};

