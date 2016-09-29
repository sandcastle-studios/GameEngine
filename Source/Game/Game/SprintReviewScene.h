#pragma once
#include <Engine/Scene/Scene.h>

class Time;

class SprintReviewScene : public Scene
{
public:
	SprintReviewScene();
	~SprintReviewScene();

	virtual void Update(const Time & aDeltaTime) override;
	virtual void Render() override;

private:
	void CreateFactories();
};

