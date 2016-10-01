#include "stdafx.h"
#include "SprintReviewScene.h"
#include <Engine\Component\Factory\ComponentFactory.h>
#include <Engine/Model/ModelInstance.h>
#include <Engine\Component\ModelComponent.h>
#include <Engine\Component\LightComponent.h>
#include <Engine\GameObject\GameObject.h>
#include <Engine\Model\AssimpModel.h>
#include <Engine/Effect/StandardEffect.h>
#include <Engine\Camera/Camera.h>



SprintReviewScene::SprintReviewScene()
{
	CreateFactories();
}

SprintReviewScene::~SprintReviewScene()
{
}

void SprintReviewScene::Update(const SB::Time & aDeltaTime)
{
	SB::Scene::Update(aDeltaTime);
}

void SprintReviewScene::Render()
{
	SB::Scene::Render();
}

void SprintReviewScene::CreateFactories()
{
	PreCreateComponentFactory<ModelComponent>();
	PreCreateComponentFactory<LightComponent>();

	std::shared_ptr<SB::GameObject> enemy = CreateGameObject();

	SharedPtrComponent<ModelComponent> prettyModel(GetComponentFactory<ModelComponent>()->CreateComponent());
	std::shared_ptr<SB::AssimpModel> model = std::make_shared<SB::AssimpModel>(myEffect, "models/Modelviewer_Exempelmodell/K11_1415.fbx");
	prettyModel->SetModel(model);

	SharedPtrComponent<ModelComponent> moarModel(GetComponentFactory<ModelComponent>()->CreateComponent());
	std::shared_ptr<SB::AssimpModel> actualModel = std::make_shared<SB::AssimpModel>(myEffect, "models/Stefan/testSpheres.fbx");
	moarModel->SetModel(actualModel);

	enemy->AddComponent<ModelComponent>(prettyModel);
	enemy->AddComponent<ModelComponent>(moarModel);

	myObjects.Add(enemy);

	SetCameraOrientation(model->GetBoundingBox().GetCenter() + SB::Vector3f(0.f, 0.f, -model->GetBoundingBox().GetSize().z * 1.5f));
}
