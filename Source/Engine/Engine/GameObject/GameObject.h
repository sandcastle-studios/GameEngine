#pragma once
#include "Engine\Component\Pointer\SharedPtrComponent.h"

class Scene;
class BaseComponent;

class GameObject
{
public:
	GameObject();
	~GameObject();

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

	GrowingArray<GrowingArray<SharedPtrComponent<BaseComponent>, size_t>, size_t> myComponents;


private:
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
