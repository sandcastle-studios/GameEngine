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
#include "Engine\Camera\CameraController.h"

Scene::Scene(const char * aSkyboxPath)
{
	myCamera = std::make_unique<Camera>();

	myEffect = std::make_shared<StandardEffect>();
	myEffect = std::make_shared<StandardEffect>();
	 
	if (aSkyboxPath != nullptr)
	{
		mySkybox = std::make_unique<ModelInstance>(std::make_shared<Skybox>(std::make_shared<StandardEffect>("shaders/pbr/vertex.fx", "VShader", "shaders/pbr/skybox.fx", "PShader"), std::make_shared<Texture>(aSkyboxPath)));
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

	std::shared_ptr<CameraController> & cc = myCameraControllers.Top();
	if (cc != nullptr)
	{
		CameraControllerResult result = cc->Update(aDeltaTime, *myCamera);
		if (result == CameraControllerResult::ePassControl)
		{
			myCameraControllers.Pop();
		}
	}

	myTime += aDeltaTime;
}

void Scene::Render()
{
	myCamera->ApplyToVS();

	if (mySkybox != nullptr)
	{
		mySkybox->SetMatrix(Matrix44f::CreateTranslation(myCamera->GetPosition()));
		mySkybox->InstantRender();
		Engine::GetInstance().GetRenderer().GetBackBuffer()->GetDepthBuffer()->Clear();
	}

	for (size_t iFactory = 0; iFactory < myFactories.Size(); ++iFactory)
	{
		if (myFactories[iFactory] != nullptr)
		{
			myFactories[iFactory]->Render();
		}
	}
}

void Scene::PushCameraController(const std::shared_ptr<CameraController> & aCameraController)
{
	myCameraControllers.Push(aCameraController);
}
