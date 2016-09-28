#include "stdafx.h"
#include "StefanScene.h"
#include <Engine\Component\Factory\ComponentFactory.h>
#include <Engine/Model/ModelInstance.h>
#include <Engine\Component\ModelComponent.h>
#include <Engine\Component\LightComponent.h>
#include <Engine\GameObject\GameObject.h>
#include <Engine\Model\AssimpModel.h>
#include <Engine/Effect/StandardEffect.h>
#include <Engine\Camera/Camera.h>
StefanScene::StefanScene()
{
	CreateFactories();


}

StefanScene::~StefanScene()
{
}

void StefanScene::Update(const Time & aDeltaTime)
{
	Scene::Update(aDeltaTime);
}

void StefanScene::Render()
{
	Scene::Render();
}

void StefanScene::CreateFactories()
{
	AddComponentFactory<ModelComponent>();
	AddComponentFactory<LightComponent>();

	std::shared_ptr<GameObject> enemy = std::make_shared<GameObject>();

	//GetComponentFactory<ModelComponent>()->CreateComponent();

	SharedPtrComponent<ModelComponent> prettyModel (GetComponentFactory<ModelComponent>()->CreateComponent());
	std::shared_ptr<AssimpModel> model = std::make_shared<AssimpModel>(myEffect, "models/Stefan/testSpheres.fbx");
	prettyModel->SetModel(std::make_shared<ModelInstance>(model));

	GetCamera().SetPosition(model->GetBoundingBox().GetCenter() + Vector3f(0.f, 0.f, -model->GetBoundingBox().GetSize().z * 5.f));
	
	enemy->AddComponent<ModelComponent>(prettyModel);
}
