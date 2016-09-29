#include "stdafx.h"
#include "BaseComponent.h"


BaseComponent::BaseComponent()
{
}

BaseComponent::~BaseComponent()
{
}

void BaseComponent::Update(const Time & aDeltaTime)
{
}

void BaseComponent::Render() const
{
}

void BaseComponent::SetGameObject(GameObject & anObject)
{
	myObject = &anObject;
}
