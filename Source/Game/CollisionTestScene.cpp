#include "stdafx.h"
#include "CollisionTestScene.h"
#include "imgui.h"

#include <Engine\Component\Factory\ComponentFactory.h>
#include <Engine/Model/ModelInstance.h>
#include <Engine\Component\ModelComponent.h>
#include <Engine\Component\LightComponent.h>
#include <Engine\GameObject\GameObject.h>
#include <Engine\Model\AssimpModel.h>
#include <Engine/Effect/StandardEffect.h>
#include <Engine\Camera/Camera.h>

CollisionTestScene::CollisionTestScene()
{
	CreateFactories();

	//GetCamera().SetPosition(Vector3f(0.f, 0.f, -200.f));
}


CollisionTestScene::~CollisionTestScene()
{
}

void CollisionTestScene::Update(const Time & aDeltaTime)
{
	ImGui::SetNextWindowPos({ 16, 16 }, ImGuiSetCond_Once);
	ImGui::SetNextWindowSize({ 375, 400 }, ImGuiSetCond_Once);
	ImGui::SetNextWindowCollapsed(true, ImGuiSetCond_Once);

	if (ImGui::Begin("Debug Window"))
	{
		static bool checked;
		ImGui::Checkbox("Checked", &checked);
	}

	ImGui::End();

	Scene::Update(aDeltaTime);
}

void CollisionTestScene::Render()
{
	Scene::Render();
}

void CollisionTestScene::CreateFactories()
{
	AddComponentFactory<ModelComponent>();
	AddComponentFactory<LightComponent>();

	std::shared_ptr<GameObject> enemy = std::make_shared<GameObject>();

	//GetComponentFactory<ModelComponent>()->CreateComponent();

	SharedPtrComponent<ModelComponent> prettyModel(GetComponentFactory<ModelComponent>()->CreateComponent());
	std::shared_ptr<AssimpModel> model = std::make_shared<AssimpModel>(myEffect, "models/Asteroid/AsteroidPillarHuge1.fbx");
	prettyModel->SetModel(std::make_shared<ModelInstance>(model));



	GetCamera().SetPosition(model->GetBoundingBox().GetCenter() + Vector3f(0.f, 0.f, -model->GetBoundingBox().GetSize().z * 1.5f));

	enemy->AddComponent<ModelComponent>(prettyModel);
}