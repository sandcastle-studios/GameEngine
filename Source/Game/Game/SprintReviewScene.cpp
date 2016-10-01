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
	PreCreateComponentFactory<SB::ModelComponent>();
	PreCreateComponentFactory<SB::LightComponent>();

	std::shared_ptr<SB::GameObject> enemy = CreateGameObject();

	SB::SharedPtrComponent<SB::ModelComponent> prettyModel(GetComponentFactory<SB::ModelComponent>()->CreateComponent());
	std::shared_ptr<SB::AssimpModel> model = std::make_shared<SB::AssimpModel>("models/Modelviewer_Exempelmodell/K11_1415.fbx");
	prettyModel->SetModel(model);

	SB::SharedPtrComponent<SB::ModelComponent> moarModel(GetComponentFactory<SB::ModelComponent>()->CreateComponent());
	std::shared_ptr<SB::AssimpModel> actualModel = std::make_shared<SB::AssimpModel>("models/Stefan/testSpheres.fbx");
	moarModel->SetModel(actualModel);

	enemy->AddComponent<SB::ModelComponent>(prettyModel);
	enemy->AddComponent<SB::ModelComponent>(moarModel);

	myObjects.Add(enemy);

	SetCameraOrientation(model->GetBoundingBox().GetCenter() + SB::Vector3f(0.f, 0.f, -model->GetBoundingBox().GetSize().z * 1.5f));
}
