#include "stdafx.h"
#include "Scene.h"
#include "ModelInstance.h"
#include "Texture.h"
#include "Skybox.h"
#include "Camera.h"
#include "DXRenderer.h"
#include "RenderTexture.h"
#include "DepthBuffer.h"
#include "SkyboxEffect.h"
#include "StandardEffect.h"

Scene::Scene(const char * aSkyboxPath)
{
	myCamera = std::make_unique<Camera>();

	myEffect = std::make_shared<StandardEffect>();
	mySkyboxEffect = std::make_shared<SkyboxEffect>();

	if (aSkyboxPath != nullptr)
	{
		mySkybox = std::make_unique<ModelInstance>(std::make_shared<Skybox>(mySkyboxEffect, std::make_shared<Texture>(aSkyboxPath)));
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
		mySkybox->SetMatrix(Matrix44f::CreateTranslation(GetCamera().GetPosition()));
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
