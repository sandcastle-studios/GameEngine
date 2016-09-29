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
#include "Engine/GameObject/GameObject.h"

Scene::Scene(const char* aName, const char * aSkyboxPath)
{
	myCamera = std::make_unique<Camera>();

	myEffect = std::make_shared<StandardEffect>();
	myName = aName;
	if (aSkyboxPath != nullptr)
	{
		mySkybox = std::make_unique<ModelInstance>(std::make_shared<Skybox>(std::make_shared<StandardEffect>("shaders/pbr/vertex.fx", "VShader", "shaders/pbr/skybox.fx", "PShader"), std::make_shared<Texture>(aSkyboxPath)));
	}
	else
	{
		mySkybox = nullptr;
	}

	myScheduledRemovals = 0;

	myFactories.Reserve(8);
}

Scene::~Scene()
{
}

void Scene::Update(const Time & aDeltaTime)
{
	if (myScheduledRemovals > 0)
	{
		for (int i = static_cast<int>(myObjects.Size()) - 1; i >= 0; i--)
		{
			if (myObjects[static_cast<unsigned short>(i)]->IsRemoved())
			{
				auto obj = myObjects[static_cast<unsigned short>(i)];
				myObjects.RemoveCyclicAtIndex(static_cast<unsigned short>(i));
				myScheduledRemovals--;

				Engine::GetLogger().LogInfo("Refcount after removal: {0}", obj.use_count());

				if (myScheduledRemovals == 0)
				{
					break;
				}
			}
		}

		myScheduledRemovals = 0;
	}

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
void Scene::CreateGameObjectBuffer(const unsigned short aObjectCount)
{
	myObjects.Reserve(aObjectCount);
}

std::shared_ptr<GameObject> Scene::CreateGameObject(const GameObjectData* aData)
{
	std::shared_ptr<GameObject> go = std::make_shared<GameObject>(*this, aData);
	myObjects.Add(go);
	return go;
}

void Scene::IncrementRemovalCounter()
{
	myScheduledRemovals++;
}

std::shared_ptr<GameObject> Scene::CreateAndAddModel(const std::string & aPath, const Vector3f & aPosition, const Vector3f & aScale /*= Vector3f::One*/, const Quaternion & aOrientation /*= Quaternion()*/)
{
	return CreateObjectWithModel(std::make_shared<AssimpModel>(myEffect, aPath), aPosition, aScale, aOrientation);
}

std::shared_ptr<GameObject> Scene::CreateObjectWithModel(const std::shared_ptr<Model> & aModel, const Vector3f & aPosition, const Vector3f & aScale /*= Vector3f::One*/, const Quaternion & aOrientation /*= Quaternion()*/)
{
	std::shared_ptr<GameObject> object = std::make_shared<GameObject>(*this, nullptr);
	object->SetPosition(aPosition);
	object->SetScale(aScale);
	object->SetRotation(aOrientation);

	SharedPtrComponent<ModelComponent> modelComponent = GetComponentFactory<ModelComponent>()->CreateComponent();
	modelComponent->SetModel(aModel);
	object->AddComponent(modelComponent);

	myObjects.Add(object);

	return object;
}

void Scene::UpdatePerspective(float aFoV, float aWidth, float aHeight, float aNearPlane, float aFarPlane) const
{
	myCamera->CreatePerspective(aFoV, aWidth, aHeight, aNearPlane, aFarPlane);
}
