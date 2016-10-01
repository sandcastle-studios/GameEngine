#pragma once
#include "Engine\Component\Pointer\SharedPtrComponent.h"

namespace ENGINE_NAMESPACE
{
	class Scene;
	class BaseComponent;

	class GameObject
	{
	public:
		GameObject(Scene & aScene);
		~GameObject();

		void SetPosition(const Vector3f & aPosition);
		void SetRotation(const Quaternion & aRotation);
		void SetScale(const Vector3f & aScale);

		const Vector3f & GetPosition() const;
		const Quaternion & GetRotation() const;
		const Vector3f &  GetScale() const;

		Matrix44f GetTransformation() const;

		Scene & GetScene();
		const Scene & GetScene() const;

		template <typename TStateType>
		TStateType & GetState();

		template <typename TStateType>
		const TStateType & GetState() const;

		template <typename TComponentType>
		void AddComponent(const SharedPtrComponent<TComponentType> & aComponent);

		template<>
		void AddComponent<BaseComponent>(const SharedPtrComponent<BaseComponent> & aComponent);

		template <typename TComponentType>
		SharedPtrComponent<TComponentType> GetComponent(const size_t & anIndex = 0);

		template <typename TComponentType>
		const SharedPtrComponent<TComponentType> GetComponent(const size_t & anIndex = 0)const;

		template <typename TComponentType>
		size_t GetComponentCount() const;

		void Remove();

		bool IsRemoved() const;

		const std::string & GetIdentifier() const;
		void SetIdentifier(const std::string &aIdentifier);

		void SetParent(const std::shared_ptr<GameObject> & aParent);
		const std::shared_ptr<GameObject> & GetParent() const;

		const GrowingArray<GameObject*> GetChildren() const;

	private:
		GrowingArray<GrowingArray<SharedPtrComponent<BaseComponent>, size_t>, size_t> myComponents;
		std::string myID;
		Vector3f myPosition;
		Vector3f myScale;
		Quaternion myRotation;
		Scene * myScene;
		bool myIsRemoved;
		std::shared_ptr<GameObject> myParent;
	public:
		GrowingArray<GameObject*> myChildren;
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
		myComponents[id].GetLast()->SetGameObject(*this);
	}

	template <typename TComponentType>
	SharedPtrComponent<TComponentType>
		GameObject::GetComponent(const size_t & anIndex/* = 0*/)
	{
		size_t id = UniqeIdentifier<BaseComponent>::GetID<TComponentType>();
		if (myComponents.Size() <= id || myComponents[id].Size() <= anIndex)
		{
			return SharedPtrComponent<TComponentType>();
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
			return SharedPtrComponent<TComponentType>();
		}
		return SharedPtrComponent<TComponentType>::CastFrom(myComponents[id][anIndex]);
	}

	template <typename TComponentType>
	size_t GameObject::GetComponentCount() const
	{
		size_t id = UniqeIdentifier<BaseComponent>::GetID<TComponentType>();

		if (id < myComponents.Size())
		{
			return myComponents[id].Size();
		}
		else
		{
			return 0;
		}
	}

	inline bool GameObject::IsRemoved() const
	{
		return myIsRemoved;
	}

	inline const std::shared_ptr<GameObject> & GameObject::GetParent() const
	{
		return myParent;
	}
}
