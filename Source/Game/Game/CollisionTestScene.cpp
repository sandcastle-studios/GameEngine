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
#include "Utilities\Intersection\IntersectionShapes\SphereIntersection.h"
#include "..\Utilities\Utilities\Intersection\IntersectionTests.h"

CollisionTestScene::CollisionTestScene(const char * aPoppyName) : Scene(aPoppyName)
{
	CreateFactories();

	GetCamera().SetPosition(Vector3f(0.f, 0.f, -3.f));

	myCollisionSphere1 = std::make_unique<SphereIntersection>();
	myCollisionSphere2 = std::make_unique<SphereIntersection>();
}


CollisionTestScene::~CollisionTestScene()
{
}

void CollisionTestScene::Update(const Time & aDeltaTime)
{
	ImGui::SetNextWindowPos({ 16, 16 }, ImGuiSetCond_Once);
	ImGui::SetNextWindowSize({ 375, 400 }, ImGuiSetCond_Once);
	ImGui::SetNextWindowCollapsed(true, ImGuiSetCond_Once);


	if (ImGui::Begin("Collision", nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse))
	{
		if (ImGui::CollapsingHeader("Object 1") == true)
		{
			Vector3f tempVector = myTestObject1->GetPosition();

			ImGui::SliderFloat("X", &tempVector.x, -3.f, 3.f);
			ImGui::SliderFloat("Y", &tempVector.y, -3.f, 3.f);
			ImGui::SliderFloat("Z", &tempVector.z, -3.f, 3.f);

			myTestObject1->SetPosition(tempVector);
			myCollisionSphere1->UpdatePosition(tempVector);
		}

		
		if (ImGui::CollapsingHeader("Object 2") == true)
		{

			Vector3f tempVector = myTestObject2->GetPosition();

			ImGui::SliderFloat("X", &tempVector.x, -3.f, 3.f);
			ImGui::SliderFloat("Y", &tempVector.y, -3.f, 3.f);
			ImGui::SliderFloat("Z", &tempVector.z, -3.f, 3.f);

			myTestObject2->SetPosition(tempVector);
			myCollisionSphere2->UpdatePosition(tempVector);
		}

		if (Intersection::SphereVsSphere(*myCollisionSphere1, *myCollisionSphere2) == true)
		{
			ImGui::Text("Collision!");
		}
		else
		{
			ImGui::Text("void!!!");
		}


		
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
	std::shared_ptr<AssimpModel> model = std::make_shared<AssimpModel>(myEffect, "models/Modelviewer_Exempelmodell/K11_1415.fbx");
	prettyModel->SetModel(model);

	SharedPtrComponent<ModelComponent> moarModel(GetComponentFactory<ModelComponent>()->CreateComponent());
	std::shared_ptr<AssimpModel> actualModel = std::make_shared<AssimpModel>(myEffect, "models/Stefan/testSpheres.fbx");
	moarModel->SetModel(actualModel);

	myTestObject1->AddComponent<ModelComponent>(prettyModel);
	myTestObject2->AddComponent<ModelComponent>(moarModel);

	myObjects.Add(myTestObject1);
	myObjects.Add(myTestObject2);

	GetCamera().SetPosition(model->GetBoundingBox().GetCenter() + Vector3f(0.f, 0.f, -model->GetBoundingBox().GetSize().z * 1.5f));
	
	//myTestObject1->SetMatrix(myTestObject1->GetMatrix() * Matrix44f::CreateScale(0.01f, 0.01f, 0.01f));
	//myTestObject2->SetMatrix(myTestObject2->GetMatrix() * Matrix44f::CreateScale(0.01f, 0.01f, 0.01f));
	
	
	myObjects.Add(enemy);
	
	
}