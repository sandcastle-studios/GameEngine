#pragma once
#include "Engine\Scene\Scene.h"

class SoundTestScene : public Scene
{
public:
	SoundTestScene();
	~SoundTestScene();

	virtual void Update(const Time & aDeltaTime) override;

	virtual void Render() override;
private:
	bool myPlaying;
	float mySoundLoop;
};

