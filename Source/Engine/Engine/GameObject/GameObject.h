#pragma once
#include "Engine\Component\Pointer\SharedPtrComponent.h"

class Scene;
class BaseComponent;

class GameObject
{
public:
	GameObject();
	~GameObject();

	const Vector3f & GetPosition() const;
	const Quaternion & GetRotation() const;
	Matrix44f GetTransformation() const;

	Scene & GetScene();
	const Scene & GetScene() const;

	template <typename TStateType>
	TStateType & GetState();

	template <typename TStateType>
	const TStateType & GetState() const;

	template <typename TComponentType>
	void AddComponent(const SharedPtrComponent<TComponentType> & aComponent);

	template <typename TComponentType>
	SharedPtrComponent<TComponentType> GetComponent(const size_t & anIndex = 0);

	template <typename TComponentType>
	const SharedPtrComponent<TComponentType> GetComponent(const size_t & anIndex = 0)const;

	template <typename TComponentType>
	size_t GetComponentCount() const;

private:
	GrowingArray<GrowingArray<SharedPtrComponent<BaseComponent>, size_t>, size_t> myComponents;
	Vector3f myPosition;
	Quaternion myRotation;
	Scene * myScene;
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
void GameObject::AddComponent(const SharedPtrComponent<TComponentType> & aComponent)
{
	size_t id = UniqeIdentifier<BaseComponent>::GetID<TComponentType>();
	size_t nextID = UniqeIdentifier<BaseComponent>::nextTypeIndex;
	if (myComponents.Size() < nextID)
	{
		myComponents.Resize(nextID);
	}
	myComponents[id].Add(SharedPtrComponent<BaseComponent>::CastFrom(aComponent));
	myComponents[id].GetLast()->SetGameObject(std::make_shared<GameObject>(*this));
}

template <typename TComponentType>
SharedPtrComponent<TComponentType>
GameObject::GetComponent(const size_t & anIndex/* = 0*/)
{
	size_t id = UniqeIdentifier<BaseComponent>::GetID<TComponentType>();
	if (myComponents.Size() <= id || myComponents[id].Size() <= anIndex)
	{
		return nullptr;
	}
	return SharedPtrComponent<TComponentType>::CastFrom(myComponents[id][anIndex]);
}

template <typename TComponentType>
const SharedPtrComponent<TComponentType>
GameObject::GetComponent(const size_t & anIndex/* = 0*/) const
{
	size_t id = UniqeIdentifier<BaseComponent>::GetID<TComponentType>();
	if (myComponents.Size() <= id || myComponents[id].Size() <= anIndex)
	{
		return nullptr;
	}
	return SharedPtrComponent<TComponentType>::CastFrom(myComponents[id][anIndex]);
}

template <typename TComponentType>
size_t GameObject::GetComponentCount() const
{
	size_t id = UniqeIdentifier<BaseComponent>::GetID<TComponentType>();
	return myComponents[id].Size();
}
