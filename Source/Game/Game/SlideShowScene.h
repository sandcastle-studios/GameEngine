#pragma once
#include <Engine\Scene\Scene.h>

class SlideShowScene : public SB::Scene
{
public:
	SlideShowScene();
	~SlideShowScene();

	void Update(const SB::Time &aDeltaTime) override;

private:
	void NextModel();

	SB::Time myCurrentModelTime;
	SB::Time myTimePerModel;
	SB::Time myModelTransitionTime;
	SB::Vector3f myCameraFrom;

	size_t myCurrentModel;
};

