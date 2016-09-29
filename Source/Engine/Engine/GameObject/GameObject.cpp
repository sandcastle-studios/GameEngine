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
	int apa = 0;
	++apa;
}

void GameObject::SetData(const GameObjectData& aData)
{
	myID = aData.myID;
	myPosition = aData.myPosition;
	myRotation = aData.myRotation;
	myScene = aData.myScene;
}
