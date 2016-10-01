#include "stdafx.h"
#include "BaseComponent.h"

namespace ENGINE_NAMESPACE
{
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

	GameObject & BaseComponent::GetGameObject()
	{
		return *myObject;
	}

	void BaseComponent::SetGameObject(GameObject & anObject)
	{
		myObject = &anObject;
	}
}
