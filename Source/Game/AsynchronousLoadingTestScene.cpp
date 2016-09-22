#include "stdafx.h"
#include "AsynchronousLoadingTestScene.h"
#include <AssimpModel.h>
#include <ModelInstance.h>
#include <StandardEffect.h>
#include <CubeModel.h>
#include <Camera.h>

AsynchronousLoadingTestScene::AsynchronousLoadingTestScene()
{
	myObjects.push_back(std::make_shared<ModelInstance>(std::make_shared<AssimpModel>(myEffect, "models/tga_companioncube/companion.fbx"), Matrix44f::CreateTranslation(-3.f, -.5f, 15.f)));
	myObjects.push_back(std::make_shared<ModelInstance>(std::make_shared<AssimpModel>(myEffect, "models/Modelviewer_Exempelmodell/K11_1415.fbx"), Matrix44f::CreateTranslation(-3.f, 0.f, 30.f)));
	myObjects.push_back(std::make_shared<ModelInstance>(std::make_shared<AssimpModel>(myEffect, "models/enemy_character/enemy_robot.fbx"), Matrix44f::CreateTranslation(-3.f, -1.f, 45.f)));

	std::shared_ptr<Model> cubeModel = std::make_shared<CubeModel>(myEffect, Engine::GetResourceManager().Get<Texture>("grass.dds"));
	for (int i = 0; i < 60; i++)
	{
		myObjects.push_back(std::make_shared<ModelInstance>(cubeModel, Matrix44f::CreateTranslation(2.f, 0.f, static_cast<float>(i) * 2.f)));
	}

	myRenderDistance = 15.f;
	myLoadDistance = 20.f;
}

AsynchronousLoadingTestScene::~AsynchronousLoadingTestScene()
{
}

void AsynchronousLoadingTestScene::Update(const Time & aDeltaTime)
{
	GetCamera().AddPosition(Vector4f(0.f, 0.f, aDeltaTime.InSeconds() * 4.f, 1.f));

	if (GetCamera().GetPosition().z >= 45.f)
	{
		GetCamera().AddPosition(Vector3f(0.f, 0.f, -45.f));
	}
	
	Scene::Update(aDeltaTime);
}
