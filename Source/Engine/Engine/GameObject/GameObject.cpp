#include "stdafx.h"
#include "Engine\GameObject\GameObject.h"

GameObject::GameObject()
{
	myComponents.Resize(UniqeIdentifier<BaseComponent>::nextTypeIndex);
}

GameObject::GameObject(const GameObjectData& aData)
{
	SetData(aData);
}

GameObject::~GameObject()
{
}

const Vector3f & GameObject::GetPosition() const
{
	return myPosition;
}

const Quaternion & GameObject::GetRotation() const
{
	return myRotation;
}

Matrix44f GameObject::GetTransformation() const
{
	Matrix44f tempTransformation = myRotation.GenerateMatrix();
	tempTransformation.SetPosition(myPosition);
	return tempTransformation;
}

void GameObject::SetData(const GameObjectData& aData)
{
	myID = aData.myID;
	myPosition = aData.myPosition;
	myRotation = aData.myRotation;
	myScene = aData.myScene;

	for (size_t i = 0; i < aData.myComponentList.Size(); ++i)
	{
		AddComponent(aData.myComponentList[i]);
	}
}
