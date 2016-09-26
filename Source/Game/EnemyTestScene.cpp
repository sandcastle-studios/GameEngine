#include "stdafx.h"
#include "EnemyTestScene.h"
#include <Engine\Component\Factory\ComponentFactory.h>

#include <Engine\Component\ModelComponent.h>
#include <Engine\Component\LightComponent.h>
#include <Engine\GameObject\GameObject.h>

EnemyTestScene::EnemyTestScene()
{
}

EnemyTestScene::~EnemyTestScene()
{
}

void EnemyTestScene::Update(const Time & aDeltaTime)
{
	Scene::Update(aDeltaTime);
}

void EnemyTestScene::Render()
{
	Scene::Render();
}

void EnemyTestScene::CreateFactories()
{
	AddComponentFactory<ModelComponent>();
	AddComponentFactory<LightComponent>();

	std::shared_ptr<GameObject> enemy = std::make_shared<GameObject>();

	enemy->AddComponent<std::shared_ptr<ModelComponent>>(GetComponentFactory<ModelComponent>()->CreateComponent());
}
