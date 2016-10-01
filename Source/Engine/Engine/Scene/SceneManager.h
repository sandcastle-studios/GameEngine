#pragma once
#include "Engine/GameObject/GameObject.h"

namespace ENGINE_NAMESPACE
{

	class JsonScene;
	class Scene;
	class StandardEffect;


	class SceneManager
	{
	public:
		SceneManager();
		~SceneManager();

		std::shared_ptr<Scene> LoadJsonScene(const char* aFilePath);

		template<typename TSceneType, typename ...TArgs>
		std::shared_ptr<Scene> LoadScene(const TArgs & ...aArgs);

		inline std::shared_ptr<Scene> GetCurrentScene() const
		{
			return myCurrentScene;
		}


	private:
		std::shared_ptr<JsonScene> CreateScene(const char* aFilePath);
		std::shared_ptr<GameObject> LoadGameObject(DataNode aObjectNode, std::shared_ptr<Scene> aScene);
		std::unordered_map<const char*, std::shared_ptr<Scene>> myScenes;
		std::shared_ptr<Scene> myCurrentScene;

	};

	template<typename TSceneType, typename ...TArgs>
	std::shared_ptr<Scene>
		SceneManager::LoadScene(const TArgs & ...aArgs)
	{
		myCurrentScene = std::make_shared<TSceneType>(aArgs...);
		return myCurrentScene;
	}

}
