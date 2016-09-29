#include "stdafx.h"
#include "PbrTestScene.h"
#include <Engine\Model\AssimpModel.h>
#include <Engine\Model\ModelInstance.h>
#include <Engine\Effect\StandardEffect.h>
#include <Engine\Camera\Camera.h>
#include <Engine\Rendering\DXRenderer.h>
#include <Engine\Rendering\ModelRenderer.h>
#include <imgui.h>
#include <Engine\Component\Factory\ComponentFactory.h>
#include <Engine/Model/ModelInstance.h>
#include <Engine\Component\ModelComponent.h>
#include <Engine\GameObject\GameObject.h>
#include "..\Engine\Engine\Camera\Controllers\FreeSpaceCameraController.h"
#include "..\Engine\Engine\Model\CubeModel.h"

PbrTestScene::PbrTestScene()
	: Scene("spacebox.dds")
{
	// "models/Modelviewer_Exempelmodell/K11_1415.fbx")); // 
	myHead = std::make_shared<CubeModel>(myEffect, nullptr); // 
	
	auto bb = myHead->GetBoundingBox();

	auto model = GetComponentFactory<ModelComponent>()->CreateComponent();
	model->SetModel(myHead);

	std::shared_ptr<GameObject> obj = std::make_shared<GameObject>();
	obj->AddComponent(model);

	PushCameraController(std::make_shared<FreeSpaceCameraController>(5.f, 1.5f));

	myObjects.Add(obj);

	Engine::GetRenderer().GetModelRenderer().SetAmbient(.05f);
	Engine::GetRenderer().GetModelRenderer().SetDirectionalLight(0, Vector3f(1.f, -1.f, 1.f), Vector4f(1.0f, 1.0f, 1.0f, 1.f));
}

PbrTestScene::~PbrTestScene()
{
}

void PbrTestScene::Update(const Time & aDeltaTime)
{
	if (ImGui::Begin("PBR Test Scene", nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse))
	{
		ImGui::Text("Move camera with WASD, QE, Ctrl, Space and Arrow Keys.");
	}
	ImGui::End();

	//myHead->SetMatrix(Matrix44f::CreateRotateAroundY(myTime.InSeconds()) * Matrix44f::CreateTranslation(0.f, 0.f, -5.f));

	Scene::Update(aDeltaTime);
}

void PbrTestScene::Render()
{
	Scene::Render();
}
