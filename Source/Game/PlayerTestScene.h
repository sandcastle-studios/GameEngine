#pragma once
#include <Engine\Scene\Scene.h>

class PlayerTestScene : public SB::Scene
{
public:
	PlayerTestScene();
	~PlayerTestScene();


	virtual void Update(const SB::Time & aDeltaTime) override;


	virtual void Render() override;

private:
	std::shared_ptr<SB::GameObject> myPlayer;
};

