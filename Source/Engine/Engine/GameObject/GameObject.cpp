#include "stdafx.h"
#include "Engine\GameObject\GameObject.h"
#include "..\Scene\Scene.h"

namespace ENGINE_NAMESPACE
{
	int nextId = 0;
	int objCounter = 0;

	GameObject::GameObject(Scene & aScene)
	{
		myScene = &aScene;
		myIsRemoved = false;
		myID = FormatString("Object {0}", ++objCounter);

		myComponents.Resize(UniqeIdentifier<BaseComponent>::nextTypeIndex);
	}

	GameObject::~GameObject()
	{
	}

	void GameObject::SetPosition(const Vector3f & aPosition)
	{
		myPosition = aPosition;
	}

	void GameObject::SetRotation(const Quaternion & aRotation)
	{
		myRotation = aRotation;
		myRotation.Normalize();
	}

	void GameObject::SetScale(const Vector3f & aScale)
	{
		myScale = aScale;
	}

	const Vector3f & GameObject::GetPosition() const
	{
		return myPosition;
	}

	const Quaternion & GameObject::GetRotation() const
	{
		return myRotation;
	}

	const Vector3f & GameObject::GetScale() const
	{
		return myScale;
	}

	Matrix44f GameObject::GetTransformation() const
	{
		Matrix44f aRotation = myRotation.GenerateMatrix();
		Matrix44f ourTransformation = Matrix44f::CreateScale(myScale.x, myScale.y, myScale.z) * aRotation * Matrix44f::CreateTranslation(myPosition);

		if (myParent == nullptr)
		{
			return ourTransformation;
		}
		return ourTransformation * myParent->GetTransformation();
	}

	template<>
	void GameObject::AddComponent(const SharedPtrComponent<BaseComponent> & aComponent)
	{
		//Error("SLUTA ROBIN");
	}

	void GameObject::Remove()
	{
		if (myIsRemoved == false)
		{
			myScene->IncrementRemovalCounter();
			myIsRemoved = true;
		}
	}

	const std::string & GameObject::GetIdentifier() const
	{
		return myID;
	}

	void GameObject::SetIdentifier(const std::string &aIdentifier)
	{
		myID = aIdentifier;
	}

	void GameObject::SetParent(const std::shared_ptr<GameObject> & aParent)
	{
		if (myParent != nullptr)
		{
			myParent->myChildren.RemoveAtIndex(myParent->myChildren.Find(this));
		}

		myParent = aParent;

		if (myParent != nullptr)
		{
			myParent->myChildren.Add(this);
		}
	}

	const GrowingArray<GameObject*> GameObject::GetChildren() const
	{
		return myChildren;
	}
}
