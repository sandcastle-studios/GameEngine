#pragma once
#include <Engine\Scene\Scene.h>

class SlideShowScene : public Scene
{
public:
	SlideShowScene();
	~SlideShowScene();

	void Update(const Time &aDeltaTime) override;

private:
	void NextModel();

	Time myCurrentModelTime;
	Time myTimePerModel;
	Time myModelTransitionTime;
	Vector3f myCameraFrom;

	size_t myCurrentModel;
};

