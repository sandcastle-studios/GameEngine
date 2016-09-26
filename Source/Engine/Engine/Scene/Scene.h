#pragma once
#include "Utilities\Container\GrowingArray.h"

class ModelInstance;
class BaseComponentFactory;
class Camera;
class StandardEffect;

class Scene
{
public:
	Scene(const char * aSkyboxPath = nullptr);
	virtual ~Scene();

	virtual void Update(const Time & aDeltaTime);
	virtual void Render();

	Camera & GetCamera();

	template <typename TComponentFactoryType>
	void AddFactory();

protected:

	template <typename TComponentFactoryType>
	std::shared_ptr<TComponentFactoryType> GetComponentFactory();


	//ComponentFactory<std::shared_ptr<ModelComponent>> myModelComponentFactory;
	GrowingArray<std::shared_ptr<BaseComponentFactory>, size_t> myFactories;

	std::vector<std::shared_ptr<ModelInstance>> myObjects;

	std::unique_ptr<ModelInstance> mySkybox;

	std::unique_ptr<Camera> myCamera;

	std::shared_ptr<StandardEffect> myEffect;

	Time myTime;
};

template<typename TComponentFactoryType>
inline void Scene::AddFactory()
{
	size_t id = UniqeIdentifier<std::shared_ptr<BaseComponentFactory>>::GetID<TComponentFactoryType>();
	size_t nextID = UniqeIdentifier<std::shared_ptr<BaseComponentFactory>>::nextTypeIndex;
	if (myFactories.Size() < nextID)
	{
		myFactories.Resize(nextID);
	}
	myFactories[id] = std::make_shared<TComponentFactoryType>();
}


template <typename TComponentFactoryType>
std::shared_ptr<TComponentFactoryType> Scene::GetComponentFactory()
{
	size_t id = UniqeIdentifier<std::shared_ptr<BaseComponentFactory>>::GetID<TComponentFactoryType>();

	if (id >= UniqeIdentifier<BaseComponentFactory>::nextTypeIndex)
	{
		myFactories.Resize(id);
		myFactories[id] = std::make_shared<TComponentFactoryType>();
	}
	return myFactories[id];
}

