#pragma once
#include <Engine/Scene/Scene.h>

class Script;

class EnemyTestScene : public Scene
{
public:
	EnemyTestScene();
	~EnemyTestScene();

	virtual void Update(const Time & aDeltaTime) override;
	virtual void Render() override;

private:
	void CreateFactories();

	std::shared_ptr<Script> myScript;
};

