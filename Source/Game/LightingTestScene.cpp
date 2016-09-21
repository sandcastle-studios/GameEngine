#include "stdafx.h"
#include "LightingTestScene.h"
#include <AssimpModel.h>
#include <ModelInstance.h>
#include <StandardEffect.h>
#include <Camera.h>
#include <DXRenderer.h>
#include <ModelRenderer.h>

LightingTestScene::LightingTestScene()
{
	std::shared_ptr<AssimpModel> model = std::make_shared<AssimpModel>(myEffect, "models/Modelviewer_Exempelmodell/K11_1415.fbx");
	myHead = std::make_shared<ModelInstance>(model);
	myObjects.push_back(myHead);

	GetCamera().SetPosition(model->GetBoundingBox().GetCenter() + Vector3f(0.f, 0.f, -model->GetBoundingBox().GetSize().z * 1.5f));
	GetCamera().LookAt(Vector3f::Zero);

	Engine::GetRenderer().GetModelRenderer().SetDirectionalLight(0, Vector3f(0.f, 1.f, 0.f), Vector4f(0.7f, 0.7f, 0.7f, 1.f));
}

LightingTestScene::~LightingTestScene()
{
}

void LightingTestScene::Update(const Time & aDeltaTime)
{
	myHead->SetMatrix(Matrix44f::CreateRotateAroundY(myTime.InSeconds()));

	Scene::Update(aDeltaTime);
}

void LightingTestScene::Render()
{
	Scene::Render();
}
