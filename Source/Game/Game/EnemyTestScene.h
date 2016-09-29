#pragma once
#include <Engine/Scene/Scene.h>

class EnemyTestScene : public Scene
{
public:
	EnemyTestScene(const char* aName = "");
	~EnemyTestScene();

	virtual void Update(const Time & aDeltaTime) override;
	virtual void Render() override;

private:
	std::shared_ptr<GameObject> myPlayer;
	std::shared_ptr<GameObject> myEnemy;
};

