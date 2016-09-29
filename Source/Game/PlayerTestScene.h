#pragma once
#include <Engine\Scene\Scene.h>

class PlayerTestScene : public Scene
{
public:
	PlayerTestScene();
	~PlayerTestScene();


	virtual void Update(const Time & aDeltaTime) override;


	virtual void Render() override;

private:
	std::shared_ptr<GameObject> myPlayer;
};

