#include "stdafx.h"
#include "Engine\GameObject\GameObject.h"
#include "..\Scene\Scene.h"

int nextId = 0;

GameObject::GameObject(Scene & aScene, const GameObjectData * aData)
{
	myScene = &aScene;
	myScale = Vector3f::One;
	myIsRemoved = false;

	myComponents.Resize(UniqeIdentifier<BaseComponent>::nextTypeIndex);

	if (aData != nullptr)
	{
		SetData(*aData);
	}
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
	return Matrix44f::CreateScale(myScale.x, myScale.y, myScale.z) * aRotation * Matrix44f::CreateTranslation(myPosition);
}

void GameObject::SetData(const GameObjectData& aData)
{
	myID = aData.myID;
	myPosition = aData.myPosition;
	myRotation = aData.myRotation;

	for (size_t i = 0; i < aData.myComponentList.Size(); ++i)
	{
		AddComponent(aData.myComponentList[i]);
	}
}

void GameObject::Remove()
{
	if (myIsRemoved == false)
	{
		myScene->IncrementRemovalCounter();
		myIsRemoved = true;
	}
}
