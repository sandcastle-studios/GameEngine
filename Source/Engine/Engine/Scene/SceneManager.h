#pragma once

class JsonScene;
class Scene;

class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	std::shared_ptr<Scene> LoadScene(const char* aFilePath);

	template<typename TSceneType>
	std::shared_ptr<Scene> LoadScene(const char* aName);

	inline std::shared_ptr<Scene> GetCurrentScene() const
	{
		return myCurrentScene;
	}


private:
	std::shared_ptr<JsonScene> CreateScene(const char* aFilePath);

	std::unordered_map<const char*, std::shared_ptr<Scene>> myScenes;
	std::shared_ptr<Scene> myCurrentScene;
};

template<typename TSceneType>
std::shared_ptr<Scene> SceneManager::LoadScene(const char* aName)
{
	if (myScenes.find(aName) == myScenes.end())
	{
		myScenes[aName] = (std::make_shared<TSceneType>(aName));
	}
	myCurrentScene = myScenes[aName];
	return myScenes[aName];
}

