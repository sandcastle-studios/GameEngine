#pragma once

class Scene;
class BaseComponent;

struct GameObjectData
{
	std::string myID;
	Quaternion myRotation;
	Vector3f myPosition;
	std::shared_ptr<Scene> myScene;
};

class GameObject
{
public:
	GameObject();
	GameObject(const GameObjectData& aData);
	~GameObject();

	Scene & GetScene();
	const Scene & GetScene() const;

	template <typename TStateType>
	TStateType & GetState();

	template <typename TStateType>
	const TStateType & GetState() const;


	template <typename TComponentType>
	void AddComponent(const TComponentType &aComponent);

	template <typename TComponentType>
	std::shared_ptr<TComponentType> GetComponent();

	template <typename TComponentType>
	const std::shared_ptr<TComponentType> GetComponent()const;

	//ComponentFactory<std::shared_ptr<ModelComponent>> myModelComponentFactory;
	GrowingArray<std::shared_ptr<BaseComponent>, size_t> myComponents;

	inline const Vector3f& GetPosition() const
	{
		return myPosition;
	}
	inline const Quaternion& GetRotation() const
	{
		return myRotation;
	}

	void SetData(const GameObjectData& aData);

private:
	std::string myID;
	Quaternion myRotation;
	Vector3f myPosition;
	std::shared_ptr<Scene> myScene;
};

inline Scene & GameObject::GetScene()
{
	return *myScene;
}

inline const Scene & GameObject::GetScene() const
{
	return *myScene;
}

template <typename TStateType>
TStateType & GameObject::GetState()
{

}

template <typename TStateType>
const TStateType & GameObject::GetState() const
{

}

template <typename TComponentType>
void GameObject::AddComponent(const TComponentType &aComponent)
{
	size_t id = UniqeIdentifier<std::shared_ptr<BaseComponent>>::GetID<TComponentType>();
	size_t nextID = UniqeIdentifier<std::shared_ptr<BaseComponent>>::nextTypeIndex;
	if (myComponents.Size() < nextID)
	{
		myComponents.Resize(nextID);
	}
	myComponents[id] = aComponent;
}

template <typename TComponentType>
std::shared_ptr<TComponentType>
GameObject::GetComponent()
{
	size_t id = UniqeIdentifier<std::shared_ptr<BaseComponent>>::GetID<TComponentType>();
	size_t nextID = UniqeIdentifier<std::shared_ptr<BaseComponent>>::nextTypeIndex;
	if (myComponents.Size() < nextID)
	{
		AddComponent<TComponentType>();
	}
	return std::static_pointer_cast<TComponentType>(myComponents[id]);
}

template <typename TComponentType>
const std::shared_ptr<TComponentType>
GameObject::GetComponent() const
{
	size_t id = UniqeIdentifier<std::shared_ptr<BaseComponent>>::GetID<TComponentType>();
	return std::static_pointer_cast<TComponentType>(myComponents[id]);
}
