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

	GetCamera().SetPosition(Vector3f(0.f, 0.f, -3.f));
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
		static float TestFloat = 1.f;

		static bool checked;
		ImGui::Checkbox("Checked", &checked);

		ImGui::SliderFloat("test drag float", &TestFloat, 0.f, 10.f);
	}

	ImGui::End();

	if (ImGui::Begin("Window test"))
	{
		static float TestFloat1 = 1.f;

		ImGui::SliderFloat("test drag float", &TestFloat1, 0.f, 10.f);
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
	PreCreateComponentFactory<ModelComponent>();
	PreCreateComponentFactory<LightComponent>();

	std::shared_ptr<GameObject> enemy = std::make_shared<GameObject>();

	SharedPtrComponent<ModelComponent> prettyModel(GetComponentFactory<ModelComponent>()->CreateComponent());
	std::shared_ptr<AssimpModel> model = std::make_shared<AssimpModel>(myEffect, "models/unitsphere/sphere.fbx");

	std::shared_ptr<ModelInstance>tempModel = std::make_shared<ModelInstance>(model);

	tempModel->SetMatrix(tempModel->GetMatrix() * Matrix44f::CreateScale(0.01f, 0.01f, 0.01f));
	prettyModel->SetModel(tempModel);

	GetCamera().SetPosition(tempModel->GetBoundingBox().GetCenter() + Vector3f(0.f, 0.f, -model->GetBoundingBox().GetSize().z * 1.5f));

	myObjects.Add(enemy);

	
}