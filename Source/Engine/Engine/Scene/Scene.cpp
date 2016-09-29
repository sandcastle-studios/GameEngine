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
#include "Engine/Component\ModelComponent.h"
#include "Engine/Model/AssimpModel.h"
#include "Engine/Component/Factory/ComponentFactory.h"
#include "..\GameObject\GameObject.h"

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

	if (myCameraControllers.Size() > 0)
	{
		std::shared_ptr<CameraController> & cc = myCameraControllers.Top();
		if (cc != nullptr)
		{
			CameraControllerResult result = cc->Update(aDeltaTime, *myCamera);
			if (result == CameraControllerResult::ePassControl)
			{
				myCameraControllers.Pop();
			}
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

void Scene::SetCameraOrientation(const Vector3f & aCameraPosition, const Vector3f & aLookDirection /*= Vector3f(0.f, 0.f, 1.f)*/)
{
	myCamera->SetPosition(aCameraPosition);
	myCamera->LookAt(aCameraPosition + aLookDirection);
}

const Camera & Scene::GetCamera() const
{
	return *myCamera;
}

std::shared_ptr<GameObject> Scene::CreateAndAddModel(const std::string & aPath, const Vector3f & aPosition, const Vector3f & aScale /*= Vector3f::One*/, const Quaternion & aOrientation /*= Quaternion()*/)
{
	return CreateObjectWithModel(std::make_shared<AssimpModel>(myEffect, aPath), aPosition, aScale, aOrientation);
}

std::shared_ptr<GameObject> Scene::CreateObjectWithModel(const std::shared_ptr<Model> & aModel, const Vector3f & aPosition, const Vector3f & aScale /*= Vector3f::One*/, const Quaternion & aOrientation /*= Quaternion()*/)
{
	std::shared_ptr<GameObject> object = std::make_shared<GameObject>();

	SharedPtrComponent<ModelComponent> modelComponent = GetComponentFactory<ModelComponent>()->CreateComponent();
	std::shared_ptr<ModelInstance> modelInstance = std::make_shared<ModelInstance>(aModel);
	Quaternion q = aOrientation;
	q.Normalize();
	modelInstance->SetMatrix(q.GenerateMatrix() * Matrix44f::CreateScale(aScale.x, aScale.y, aScale.z) * Matrix44f::CreateTranslation(aPosition));
	modelComponent->SetModel(modelInstance);

	object->AddComponent(modelComponent);

	myObjects.Add(object);

	return object;
}

void Scene::UpdatePerspective(float aFoV, float aWidth, float aHeight, float aNearPlane, float aFarPlane) const
{
	myCamera->CreatePerspective(aFoV, aWidth, aHeight, aNearPlane, aFarPlane);
}
