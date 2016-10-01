#pragma once
#include <Engine/Scene/Scene.h>

namespace SB
{
	class Time;
}

class SprintReviewScene : public SB::Scene
{
public:
	SprintReviewScene();
	~SprintReviewScene();

	virtual void Update(const SB::Time & aDeltaTime) override;
	virtual void Render() override;

private:
	void CreateFactories();
};

