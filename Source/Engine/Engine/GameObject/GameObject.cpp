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
