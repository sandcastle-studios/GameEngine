#pragma once
#include <Engine\Scene\Scene.h>

class PlayerTestScene : public Scene
{
public:
	PlayerTestScene();
	~PlayerTestScene();

private:
	std::shared_ptr<GameObject> myPlayer;
};

