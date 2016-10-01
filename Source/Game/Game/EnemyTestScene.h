#pragma once
#include <Engine/Scene/Scene.h>

namespace SB
{
	class Script;
}

class EnemyTestScene : public SB::Scene
{
public:
	EnemyTestScene();
	~EnemyTestScene();

	virtual void Update(const SB::Time & aDeltaTime) override;
	virtual void Render() override;

private:
	void CreateFactories();

	std::shared_ptr<SB::Script> myScript;
};

