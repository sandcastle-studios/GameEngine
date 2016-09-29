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
#include "Engine\Resources\ResourceManager.h"
#include "Engine\SplashScreen\SplashScreenEffect.h"
#include <Engine\SplashScreen\SplashScreenScene.h>

CollisionTestScene::CollisionTestScene()
{
	CreateFactories();

	SetCameraOrientation(Vector3f(0.f, 0.f, -3.f));


	

}


CollisionTestScene::~CollisionTestScene()
{
}

void CollisionTestScene::Update(const Time & aDeltaTime)
{
	ImGui::SetNextWindowPos({ 16, 16 }, ImGuiSetCond_Once);
	ImGui::SetNextWindowSize({ 375, 400 }, ImGuiSetCond_Once);
	ImGui::SetNextWindowCollapsed(true, ImGuiSetCond_Once);

	if (ImGui::Begin("Object 1", nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse))
	{
		Vector3f tempVector = myTestObject1->GetPosition();

		ImGui::SliderFloat("X", &tempVector.x, -3.f, 3.f);
		ImGui::SliderFloat("Y", &tempVector.y, -3.f, 3.f);
		ImGui::SliderFloat("Z", &tempVector.z, -3.f, 3.f);

		myTestObject1->SetPosition(tempVector);
	}

	ImGui::End();

	if (ImGui::Begin("Object 2", nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse))
	{
		Vector3f tempVector = myTestObject2->GetPosition();

		ImGui::SliderFloat("X", &tempVector.x, -3.f, 3.f);
		ImGui::SliderFloat("Y", &tempVector.y, -3.f, 3.f);
		ImGui::SliderFloat("Z", &tempVector.z, -3.f, 3.f);

		myTestObject2->SetPosition(tempVector);
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
	//PreCreateComponentFactory<ModelComponent>();
	//PreCreateComponentFactory<LightComponent>();
	//
	//std::shared_ptr<GameObject> enemy = std::make_shared<GameObject>();
	//
	//SharedPtrComponent<ModelComponent> prettyModel(GetComponentFactory<ModelComponent>()->CreateComponent());
	//std::shared_ptr<AssimpModel> model = std::make_shared<AssimpModel>(myEffect, "models/unitsphere/sphere.fbx");
	//
	//SharedPtrComponent<ModelComponent> tempModel2(GetComponentFactory<ModelComponent>()->CreateComponent());
	//std::shared_ptr<AssimpModel> derpModel = std::make_shared<AssimpModel>(myEffect, "models/unitsphere/sphere.fbx");
	//
	//myTestObject1 = std::make_shared<ModelInstance>(model);
	//myTestObject2 = std::make_shared<ModelInstance>(derpModel);
	//
	//myTestObject1->SetMatrix(myTestObject1->GetMatrix() * Matrix44f::CreateScale(0.01f, 0.01f, 0.01f));
	//myTestObject2->SetMatrix(myTestObject2->GetMatrix() * Matrix44f::CreateScale(0.01f, 0.01f, 0.01f));
	//prettyModel->SetModel(myTestObject1);
	//tempModel2->SetModel(myTestObject2);
	//
	//GetCamera().SetPosition(myTestObject1->GetBoundingBox().GetCenter() + Vector3f(0.f, 0.f, -model->GetBoundingBox().GetSize().z * 1.5f));
	//
	//myObjects.Add(enemy);
	//
	
}