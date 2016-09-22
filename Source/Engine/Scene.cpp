#include "stdafx.h"
#include "Scene.h"
#include "ModelInstance.h"
#include "Texture.h"
#include "Skybox.h"
#include "Camera.h"
#include "DXRenderer.h"
#include "RenderTexture.h"
#include "DepthBuffer.h"
#include "StandardEffect.h"

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

	myLoadDistance = 100.f;
	myRenderDistance = 80.f;
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
		Vector3f center = myObjects[i]->GetBoundingBox().GetCenter();
		Vector3f toObject = (center - myCamera->GetPosition());
		float distanceToObject = toObject.Length();

		if (distanceToObject < myLoadDistance)
		{
			switch (myObjects[i]->GetModel()->GetStatus())
			{
			case ModelStatus::eNotReady:
			case ModelStatus::ePreparing:
				if (myObjects[i]->GetModel()->Prepare(true))
				{
					if (distanceToObject < myRenderDistance)
					{
						myObjects[i]->Render();
					}
				}
				break;
			case ModelStatus::eReady:
				if (distanceToObject < myRenderDistance)
				{
					myObjects[i]->Render();
				}
				break;
			}
		}
	}
}

Camera & Scene::GetCamera()
{
	return *myCamera;
}
