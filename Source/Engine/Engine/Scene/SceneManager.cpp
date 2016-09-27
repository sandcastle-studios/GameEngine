#include "stdafx.h"
#include "SceneManager.h"
#include "Engine\Scene\JsonScene.h"
#include "Engine\Scene\Scene.h"
#include "Engine\GameObject\GameObject.h"

SceneManager::SceneManager()
{
}


SceneManager::~SceneManager()
{
}

std::shared_ptr<Scene> SceneManager::LoadScene(const char* aFilePath)
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
		GameObjectData objectData;
		objectData.myID = objectNode["name"].GetString();
		objectData.myPosition = Vector3f(
			objectNode["components"][0]["localPosition"][0].GetFloat(),
			objectNode["components"][0]["localPosition"][1].GetFloat(),
			objectNode["components"][0]["localPosition"][2].GetFloat()
		);
		objectData.myRotation = Quaternion(
			objectNode["components"][0]["localRotation"][0].GetFloat(), 
			objectNode["components"][0]["localRotation"][1].GetFloat(), 
			objectNode["components"][0]["localRotation"][2].GetFloat()		//TODO: Add loop for component indices as well
		);
		objectData.myScene = newScene;

		newScene->CreateGameObject(objectData);
	}


	return newScene;
}
