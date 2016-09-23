#include "stdafx.h"
#include "Scene.h"
#include "..\Model\ModelInstance.h"
#include "..\Texture\Texture.h"
#include "..\Camera\Skybox.h"
#include "..\Camera\Camera.h"
#include "..\Rendering\DXRenderer.h"
#include "..\RenderTexture.h"
#include "..\Buffer\DepthBuffer.h"
#include "..\Effect\StandardEffect.h"

Scene::Scene(const char * aSkyboxPath)
{
	myCamera = std::make_unique<Camera>();

	myEffect = std::make_shared<StandardEffect>();
	 
	if (aSkyboxPath != nullptr)
	{
		mySkybox = std::make_unique<ModelInstance>(std::make_shared<Skybox>(myEffect, std::make_shared<Texture>(aSkyboxPath)));
	}
	else
	{
		mySkybox = nullptr;
	}
}

Scene::~Scene()
{
}

void Scene::Update(const Time & aDeltaTime)
{
	Engine::GetResourceManager().Update();

	myTime += aDeltaTime;
}

void Scene::Render()
{
	if (mySkybox != nullptr)
	{
		myCamera->ApplySkyboxMatrixToVS();
		mySkybox->InstantRender();
		Engine::GetInstance().GetRenderer().GetBackBuffer()->GetDepthBuffer()->Clear();
	}

	myCamera->ApplyToVS();

	for (size_t i = 0; i < myObjects.size(); i++)
	{
		myObjects[i]->Render();
	}
}

Camera & Scene::GetCamera()
{
	return *myCamera;
}