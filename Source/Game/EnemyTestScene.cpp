#include "stdafx.h"
#include "EnemyTestScene.h"
#include <Engine\Component\Factory\ComponentFactory.h>
#include <Engine/Model/ModelInstance.h>
#include <Engine\Component\ModelComponent.h>
#include <Engine\Component\LightComponent.h>
#include <Engine\GameObject\GameObject.h>
#include <Engine\Model\AssimpModel.h>
#include <Engine/Effect/StandardEffect.h>
#include <Engine\Camera/Camera.h>
EnemyTestScene::EnemyTestScene()
{
	CreateFactories();


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

	//GetComponentFactory<ModelComponent>()->CreateComponent();

	SharedPtrGA<ModelComponent> prettyModel (GetComponentFactory<ModelComponent>()->CreateComponent());
	std::shared_ptr<AssimpModel> model = std::make_shared<AssimpModel>(myEffect, "models/Modelviewer_Exempelmodell/K11_1415.fbx");
	prettyModel->SetModel(std::make_shared<ModelInstance>(model));
	
	//SharedPtrGA<ModelComponent> ssss = GetComponentFactory<ModelComponent>()->GetComponent(0);

	GetCamera().SetPosition(model->GetBoundingBox().GetCenter() + Vector3f(0.f, 0.f, -model->GetBoundingBox().GetSize().z * 1.5f));
	
	//enemy->AddComponent<std::shared_ptr<ModelComponent>>(prettyModel);
}
