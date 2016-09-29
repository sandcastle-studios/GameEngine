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
#include "Engine\Camera\Controllers\FreeSpaceCameraController.h"

CollisionTestScene::CollisionTestScene()
{
	myTestObject1 = CreateGameObject();
	myTestObject2 = CreateGameObject();

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


	if (ImGui::Begin("Collision", nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse))
	{
		if (ImGui::CollapsingHeader("Object 1") == true)
		{
			Vector3f tempVector1 = myTestObject1->GetPosition();
			float tempScale1 = myTestObject1->GetScale().x * 100.f;

			ImGui::SliderFloat("X1", &tempVector1.x, -3.f, 3.f);
			ImGui::SliderFloat("Y1", &tempVector1.y, -3.f, 3.f);
			ImGui::SliderFloat("Z1", &tempVector1.z, -3.f, 3.f);
			
			ImGui::SliderFloat("Scale1", &tempScale1, -0.1f, 3.f);

			myCollisionSphere1->SetRadius(tempScale1 / 2.f);

			tempScale1 /= 100.f;
			myTestObject1->SetScale(Vector3f(tempScale1, tempScale1, tempScale1));
			myTestObject1->SetPosition(tempVector1);
			myCollisionSphere1->UpdatePosition(tempVector1);
			
		}

		
		if (ImGui::CollapsingHeader("Object 2") == true)
		{

			Vector3f tempVector2 = myTestObject2->GetPosition();
			float tempScale2 = myTestObject2->GetScale().x * 100.f;

			ImGui::SliderFloat("X2", &tempVector2.x, -3.f, 3.f);
			ImGui::SliderFloat("Y2", &tempVector2.y, -3.f, 3.f);
			ImGui::SliderFloat("Z2", &tempVector2.z, -3.f, 3.f);

			ImGui::SliderFloat("Scale2", &tempScale2, -0.1f, 3.f);

			myCollisionSphere2->SetRadius(tempScale2 / 2.f);

			tempScale2 /= 100.f;
			myTestObject2->SetScale(Vector3f(tempScale2, tempScale2, tempScale2));
			myTestObject2->SetPosition(tempVector2);
			myCollisionSphere2->UpdatePosition(tempVector2);
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


	SharedPtrComponent<ModelComponent> prettyModel(GetComponentFactory<ModelComponent>()->CreateComponent());
	std::shared_ptr<AssimpModel> model = std::make_shared<AssimpModel>(myEffect, "models/unitsphere/sphere.fbx");
	prettyModel->SetModel(model);

	SharedPtrComponent<ModelComponent> moarModel(GetComponentFactory<ModelComponent>()->CreateComponent());
	std::shared_ptr<AssimpModel> actualModel = std::make_shared<AssimpModel>(myEffect, "models/unitsphere/sphere.fbx");
	moarModel->SetModel(actualModel);
	
	const float tempsize = model->GetBoundingBox().GetMaximumRadius();

	myTestObject1->AddComponent<ModelComponent>(prettyModel);
	myTestObject2->AddComponent<ModelComponent>(moarModel);

	myTestObject1->SetScale(Vector3f(0.01f, 0.01f, 0.01f));
	myTestObject2->SetScale(Vector3f(0.01f, 0.01f, 0.01f));

	myCollisionSphere1 = std::make_unique<SphereIntersection>();
	myCollisionSphere2 = std::make_unique<SphereIntersection>();

	BoundingBoxf boundingBox = model->GetBoundingBox();
	boundingBox.min = Vector4f(boundingBox.min, 1.f) * myTestObject1->GetTransformation();
	boundingBox.max = Vector4f(boundingBox.max, 1.f) * myTestObject1->GetTransformation();

	myCollisionSphere1->SetRadius(boundingBox.GetMaximumRadius());
	myCollisionSphere2->SetRadius(boundingBox.GetMaximumRadius());

	myCollisionSphere1->SetRadius(boundingBox.GetSize().x / 2.f);
	myCollisionSphere2->SetRadius(boundingBox.GetSize().x / 2.f);

	PushCameraController(std::make_shared<FreeSpaceCameraController>(5.f, 1.5f));
	SetCameraOrientation(model->GetBoundingBox().GetCenter() + Vector3f(0.f, 0.f, -model->GetBoundingBox().GetSize().z * 1.5f));
	

	
	
}