#include "stdafx.h"
#include "SceneManager.h"
#include "Engine\Scene\JsonScene.h"
#include "Engine\Scene\Scene.h"
#include "Engine\GameObject\GameObject.h"
#include "Engine\Component\ModelComponent.h"
#include <Engine\Component\Factory\ComponentFactory.h>
#include "Engine\Component\Pointer\SharedPtrComponent.h"
#include <Engine\Effect\StandardEffect.h>


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
		GameObjectData data = LoadGameObject(objectNode, newScene);
		newScene->CreateGameObject(&data);
	}


	return newScene;
}

GameObjectData SceneManager::LoadGameObject(DataNode aObjectNode, std::shared_ptr<Scene> aScene)
{
	GameObjectData objectData;
	objectData.myID = aObjectNode["name"].GetString();

	for (unsigned short i = 0; i < aObjectNode["components"].Capacity(); ++i)
	{
		std::string componentType = aObjectNode["components"][i]["type"].GetString();
		SharedPtrComponent<BaseComponent> newComponent;// = std::is_null_pointer;

		if (componentType == "Transform")
		{
			objectData.myPosition = Vector3f(
				aObjectNode["components"][i]["localPosition"][0].GetFloat(),
				aObjectNode["components"][i]["localPosition"][1].GetFloat(),
				aObjectNode["components"][i]["localPosition"][2].GetFloat()
			);
			objectData.myRotation = Quaternion(
				aObjectNode["components"][i]["localRotation"][0].GetFloat(),
				aObjectNode["components"][i]["localRotation"][1].GetFloat(),
				aObjectNode["components"][i]["localRotation"][2].GetFloat()
			);

			continue;
		}
		else if (componentType == "ModelData")
		{
			//TODO: Send texture into model comp. as well, also send desired effect/shader to use for the model
			auto && mc = aScene->GetComponentFactory<ModelComponent>()->CreateComponent();
			mc->SetModel(aObjectNode["components"][i]["modelPath"].GetString(), myStandardEffect);
			newComponent = SharedPtrComponent<BaseComponent>::CastFrom(mc);
		}
		else
		{
			Error("Unable to load component. Unrecognized component type.");
		}


		if (newComponent == nullptr)
		{
			Error("Failed to create new component");
		}

		objectData.myComponentList.Add(newComponent);
	}


	return objectData;
}

