#include "stdafx.h"
#include "SceneManager.h"
#include "Engine\Scene\JsonScene.h"
#include "Engine\Scene\Scene.h"
#include "Engine\GameObject\GameObject.h"
#include "Engine\Component\ModelComponent.h"
#include <Engine\Component\Factory\ComponentFactory.h>
#include "Engine\Component\Pointer\SharedPtrComponent.h"
#include <Engine\Effect\StandardEffect.h>

namespace ENGINE_NAMESPACE
{

	SceneManager::SceneManager()
	{
		myStandardEffect = std::make_shared<StandardEffect>();
	}


	SceneManager::~SceneManager()
	{
	}

	std::shared_ptr<Scene> SceneManager::LoadJsonScene(const char* aFilePath)
	{
		if (myScenes.find(aFilePath) == myScenes.end())
		{
			myScenes[aFilePath] = CreateScene(aFilePath);
		}

		myCurrentScene = myScenes[aFilePath]; //TODO: Set this using command line and/or Json file instead

		return myScenes[aFilePath];
	}

	std::shared_ptr<JsonScene> SceneManager::CreateScene(const char* aFilePath)
	{
		std::shared_ptr<JsonScene> newScene = std::make_shared<JsonScene>(aFilePath);

		DataDocument sceneData;
		Data::Open(aFilePath, sceneData);

		newScene->CreateGameObjectBuffer(static_cast<unsigned short>(sceneData["hierarchy"].Capacity()));

		for (unsigned short i = 0; i < static_cast<unsigned short>(sceneData["hierarchy"].Capacity()); ++i)
		{
			DataNode objectNode = sceneData["hierarchy"][i];
			LoadGameObject(objectNode, newScene);
		}


		return newScene;
	}

	std::shared_ptr<GameObject> SceneManager::LoadGameObject(DataNode aObjectNode, std::shared_ptr<Scene> aScene)
	{
		std::shared_ptr<GameObject> obj = aScene->CreateGameObject();
		obj->SetIdentifier(aObjectNode["name"].GetString());

		for (unsigned short i = 0; i < aObjectNode["components"].Capacity(); ++i)
		{
			std::string componentType = aObjectNode["components"][i]["type"].GetString();

			if (componentType == "Transform")
			{
				obj->SetPosition(Vector3f(
					aObjectNode["components"][i]["localPosition"][0].GetFloat(),
					aObjectNode["components"][i]["localPosition"][1].GetFloat(),
					aObjectNode["components"][i]["localPosition"][2].GetFloat()
				));
				obj->SetRotation(Quaternion(
					aObjectNode["components"][i]["localRotation"][0].GetFloat(),
					aObjectNode["components"][i]["localRotation"][1].GetFloat(),
					aObjectNode["components"][i]["localRotation"][2].GetFloat()
				));
				obj->SetScale(Vector3f(
					aObjectNode["components"][i]["localScale"][0].GetFloat(),
					aObjectNode["components"][i]["localScale"][1].GetFloat(),
					aObjectNode["components"][i]["localScale"][2].GetFloat()
				));
			}
			else if (componentType == "ModelData")
			{
				//TODO: Send texture into model comp. as well, also send desired effect/shader to use for the model
				auto && mc = aScene->GetComponentFactory<ModelComponent>()->CreateComponent();
				mc->SetModel(aObjectNode["components"][i]["modelPath"].GetString(), myStandardEffect);
				mc->SetMatrix(Matrix44f::CreateScale(0.01f, 0.01f, 0.01f));
				obj->AddComponent(mc);
			}
			else
			{
				Error("Unable to load component. Unrecognized component type.");
			}
		}

		for (unsigned short i = 0; i < aObjectNode["children"].Capacity(); ++i)
		{
			LoadGameObject(aObjectNode["children"][i], aScene)->SetParent(obj);
		}

		return obj;
	}

}
