#pragma once
#include "Utilities\Container\GrowingArray.h"

class GameObject;
struct GameObjectData;
class BaseComponentFactory;

template <typename TComponentFactoryType>class ComponentFactory;

class Camera;
class StandardEffect;

class Scene
{
public:
	Scene(const char* aName = "", const char* aSkyboxPath = nullptr);
	virtual ~Scene();

	virtual void Update(const Time & aDeltaTime);
	virtual void Render();

	Camera & GetCamera();

	template <typename TComponentType>
	void PreCreateComponentFactory();

	void CreateGameObjectBuffer(const unsigned short aObjectCount);
	void CreateGameObject(const GameObjectData& aData);
	template <typename TComponentType>
	std::shared_ptr<ComponentFactory<TComponentType>> GetComponentFactory();

	template <typename TComponentType>
	const std::shared_ptr<ComponentFactory<TComponentType>> GetComponentFactory()const;

protected:


	//ComponentFactory<std::shared_ptr<ModelComponent>> myModelComponentFactory;
	GrowingArray<std::shared_ptr<BaseComponentFactory>, size_t> myFactories;

	GrowingArray<std::shared_ptr<GameObject>> myObjects;

	std::unique_ptr<ModelInstance> mySkybox;

	std::unique_ptr<Camera> myCamera;

	std::shared_ptr<StandardEffect> myEffect;

	Time myTime;
	std::string myName;

};

template<typename TComponentType>
inline void Scene::PreCreateComponentFactory()
{
	size_t id = UniqeIdentifier<BaseComponentFactory>::GetID<ComponentFactory<TComponentType>>();
	size_t nextID = UniqeIdentifier<BaseComponentFactory>::nextTypeIndex;
	if (myFactories.Size() < nextID)
	{
		myFactories.Resize(nextID);
	}
	myFactories[id] = std::make_shared<ComponentFactory<TComponentType>>();
}


template <typename TComponentType>
std::shared_ptr<ComponentFactory<TComponentType>> Scene::GetComponentFactory()
{
	size_t id = UniqeIdentifier<BaseComponentFactory>::GetID<ComponentFactory<TComponentType>>();
	size_t nextID = UniqeIdentifier<BaseComponentFactory>::nextTypeIndex;
	if (myFactories.Size() < nextID || myFactories[id] == nullptr)
	{
		PreCreateComponentFactory<TComponentType>();
	}
	return std::static_pointer_cast<ComponentFactory<TComponentType>>(myFactories[id]);
}

template <typename TComponentType>
const std::shared_ptr<ComponentFactory<TComponentType>> Scene::GetComponentFactory() const
{
	size_t id = UniqeIdentifier<BaseComponentFactory>::GetID<ComponentFactory<TComponentType>>();
	return std::static_pointer_cast<ComponentFactory<TComponentType>>(myFactories[id]);

}

