#include "stdafx.h"
#include "Engine\Scene\Scene.h"
#include "Engine\Model\ModelInstance.h"
#include "Engine\Texture\Texture.h"
#include "Engine\Camera\Skybox.h"
#include "Engine\Camera\Camera.h"
#include "Engine\Rendering\DXRenderer.h"
#include "Engine\Texture\RenderTexture.h"
#include "Engine\Buffer\DepthBuffer.h"
#include "Engine\Effect\StandardEffect.h"
#include "Engine\Component\Factory\BaseComponentFactory.h"
#include "Engine\Effect\SkyboxEffect.h"

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

	myFactories.Reserve(8);
}

Scene::~Scene()
{
}

void Scene::Update(const Time & aDeltaTime)
{
	for (size_t iFactory = 0; iFactory < myFactories.Size(); ++iFactory)
	{
		if (myFactories[iFactory] != nullptr)
		{
			myFactories[iFactory]->Update(aDeltaTime);
		}
	}

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

	for (size_t iFactory = 0; iFactory < myFactories.Size(); ++iFactory)
	{
		if (myFactories[iFactory] != nullptr)
		{
			myFactories[iFactory]->Render();
		}
	}
}

Camera & Scene::GetCamera()
{
	return *myCamera;
}
