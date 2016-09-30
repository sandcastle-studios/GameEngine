#pragma once
#include "Utilities\Container\GrowingArray.h"
#include "Engine\Texture\TextureCube.h"

class GameObject;
class BaseComponentFactory;

template <typename TComponentFactoryType>class ComponentFactory;

class Camera;
class StandardEffect;
class CameraController;

template <typename TBufferType>
class ConstantBuffer;

struct MipMapStruct
{
	unsigned int actualValue;
	Vector3f trash;
};

class Scene
{
public:
	Scene(const char * aSkyboxPath = nullptr);
	virtual ~Scene();

	void PushCameraController(const std::shared_ptr<CameraController> & aCameraController);

	virtual void Update(const Time & aDeltaTime);
	virtual void Render();

	Camera & GetCamera();

	template <typename TComponentType>
	void AddComponentFactory();

protected:
	Stack<std::shared_ptr<CameraController>> myCameraControllers;
	template <typename TComponentType>
	std::shared_ptr<ComponentFactory<TComponentType>> GetComponentFactory();

	template <typename TComponentType>
	const std::shared_ptr<ComponentFactory<TComponentType>> GetComponentFactory()const;

	//ComponentFactory<std::shared_ptr<ModelComponent>> myModelComponentFactory;
	GrowingArray<std::shared_ptr<BaseComponentFactory>, size_t> myFactories;

	std::vector<std::shared_ptr<GameObject>> myObjects;

	std::unique_ptr<ModelInstance> mySkybox;

	std::unique_ptr<Camera> myCamera;

	std::shared_ptr<StandardEffect> myEffect;

	Time myTime;

	std::shared_ptr<TextureCube> myTextureCube;
	std::shared_ptr<ConstantBuffer<MipMapStruct>> myMipmapBuffer;
};

template<typename TComponentType>
inline void Scene::AddComponentFactory()
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
		AddComponentFactory<TComponentType>();
	}
	return std::static_pointer_cast<ComponentFactory<TComponentType>>(myFactories[id]);
}

template <typename TComponentType>
const std::shared_ptr<ComponentFactory<TComponentType>> Scene::GetComponentFactory() const
{
	size_t id = UniqeIdentifier<BaseComponentFactory>::GetID<ComponentFactory<TComponentType>>();
	return std::static_pointer_cast<ComponentFactory<TComponentType>>(myFactories[id]);

}

