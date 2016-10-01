#include "stdafx.h"
#include "Engine\Scene\Scene.h"
#include "Engine\Model\ModelInstance.h"
#include "Engine\Texture\Texture.h"
#include "Engine\Camera\Skybox.h"
#include "Engine\Camera\Camera.h"
#include "Engine\Rendering\DXRenderer.h"
#include "Engine\Texture\RenderTexture.h"
#include "Engine\Buffer\DepthBuffer.h"
#include "Engine\Component\Factory\BaseComponentFactory.h"
#include "Engine\Camera\CameraController.h"
#include "Engine/Component\ModelComponent.h"
#include "Engine/Model/AssimpModel.h"
#include "Engine/Component/Factory/ComponentFactory.h"
#include "Engine/GameObject/GameObject.h"
#include <imgui.h>
#include <Engine/Effect/SkyboxEffect.h>

namespace ENGINE_NAMESPACE
{

	Scene::Scene(const char* aName, const char * aSkyboxPath)
	{
		myCamera = std::make_unique<Camera>();

		myName = aName;
		if (aSkyboxPath != nullptr)
		{
			std::shared_ptr<Effect> skyboxShader = std::make_shared<SkyboxEffect>();
			mySkybox = std::make_unique<ModelInstance>(std::make_shared<Skybox>(std::make_shared<Texture>(aSkyboxPath)));
			mySkybox->SetEffect(skyboxShader);
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

	void DebugObject(GameObject & obj)
	{
		ImGui::Text(FormatString("Local Position {0};{1};{2}", obj.GetPosition().x, obj.GetPosition().y, obj.GetPosition().z).c_str());
		Matrix44f m = obj.GetTransformation();
		ImGui::Text(FormatString("World Position {0};{1};{2}", m.GetPosition().x, m.GetPosition().y, m.GetPosition().z).c_str());
		ImGui::Text(FormatString("Local Scale {0};{1};{2}", obj.GetScale().x, obj.GetScale().y, obj.GetScale().z).c_str());

		const GrowingArray<GameObject*> & children = obj.GetChildren();
		for (unsigned short i = 0; i < children.Size(); i++)
		{
			if (ImGui::CollapsingHeader(children[i]->GetIdentifier().c_str()))
			{
				DebugObject(*children[i]);
			}
		}
	}

	void Scene::Update(const Time & aDeltaTime)
	{
		//if (myScheduledRemovals > 0)
		{
			for (int i = static_cast<int>(myObjects.Size()) - 1; i >= 0; i--)
			{
				if (myObjects[static_cast<unsigned short>(i)]->IsRemoved())
				{
					auto obj = myObjects[static_cast<unsigned short>(i)];
					myObjects.RemoveCyclicAtIndex(static_cast<unsigned short>(i));
					myScheduledRemovals--;

					// Engine::GetLogger().LogInfo("Refcount after removal: {0}", obj.use_count());

					if (myScheduledRemovals == 0)
					{
						//break;
					}
				}
			}

			//myScheduledRemovals = 0;
		}

		/*if (ImGui::Begin("Objects in scene"))
		{
			for (unsigned short i = 0; i < myObjects.Size(); i++)
			{
				const std::shared_ptr<GameObject> & obj = myObjects[i];
				if (obj->IsRemoved() == false)
				{
					if (obj->GetParent() == nullptr)
					{
						if (ImGui::CollapsingHeader(obj->GetIdentifier().c_str()))
						{
							DebugObject(*obj);
						}
					}
				}
			}
		}
		ImGui::End();*/

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

	std::shared_ptr<GameObject> Scene::CreateGameObject()
	{
		std::shared_ptr<GameObject> go;
		go = std::make_shared<GameObject>(*this);
		myObjects.Add(go);
		return go;
	}

	void Scene::IncrementRemovalCounter()
	{
		myScheduledRemovals++;
	}

	std::shared_ptr<GameObject> Scene::CreateAndAddModel(const std::string & aPath, const Vector3f & aPosition, const Vector3f & aScale /*= Vector3f::One*/, const Quaternion & aOrientation /*= Quaternion()*/)
	{
		return CreateObjectWithModel(std::make_shared<AssimpModel>(aPath), aPosition, aScale, aOrientation);
	}

	std::shared_ptr<GameObject> Scene::CreateObjectWithModel(const std::shared_ptr<Model> & aModel, const Vector3f & aPosition, const Vector3f & aScale /*= Vector3f::One*/, const Quaternion & aOrientation /*= Quaternion()*/)
	{
		std::shared_ptr<GameObject> object = CreateGameObject();
		object->SetPosition(aPosition);
		object->SetScale(aScale);
		object->SetRotation(aOrientation);

		SharedPtrComponent<ModelComponent> modelComponent = GetComponentFactory<ModelComponent>()->CreateComponent();
		modelComponent->SetModel(aModel);
		object->AddComponent(modelComponent);

		return object;
	}

	void Scene::UpdatePerspective(float aFoV, float aWidth, float aHeight, float aNearPlane, float aFarPlane) const
	{
		myCamera->CreatePerspective(aFoV, aWidth, aHeight, aNearPlane, aFarPlane);
	}

}
