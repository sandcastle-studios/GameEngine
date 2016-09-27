#include "stdafx.h"
#include "Engine\GameObject\GameObject.h"

GameObject::GameObject()
{
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
}
