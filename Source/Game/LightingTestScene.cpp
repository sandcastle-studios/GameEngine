#include "stdafx.h"
#include "LightingTestScene.h"
#include <AssimpModel.h>
#include <ModelInstance.h>
#include <StandardEffect.h>
#include <Camera.h>
#include "..\Engine\ConstantBuffer.h"

LightingTestScene::LightingTestScene()
{
	std::shared_ptr<AssimpModel> model = std::make_shared<AssimpModel>(myEffect, "models/tga_companioncube/companion.fbx");
	std::shared_ptr<ModelInstance> instance = std::make_shared<ModelInstance>(model);
	myObjects.push_back(instance);

	GetCamera().SetPosition(Vector3f(-1.f, 1.f, -1.f) * 3.f);
	GetCamera().LookAt(Vector3f::Zero);

	myConstantBuffer = std::make_unique<ConstantBuffer<BlendCBuffer>>();
}

LightingTestScene::~LightingTestScene()
{
}

void LightingTestScene::Render()
{
	myConstantBuffer->UpdateData(BlendCBuffer
	{
		Vector4f(1.f, 0.f, 0.f, 1.f)
	});
	myConstantBuffer->BindToPS(1);
	Scene::Render();
}
