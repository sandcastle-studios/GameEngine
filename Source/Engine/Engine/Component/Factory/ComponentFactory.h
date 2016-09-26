#pragma once
#include <Utilities/Container/GrowingArray.h>
#include "Engine/Component/Factory/BaseComponentFactory.h"

template <typename TComponentType>
class ComponentFactory : public BaseComponentFactory
{
public:
	ComponentFactory();
	~ComponentFactory();

	std::shared_ptr<TComponentType> CreateComponent();

private:
	GrowingArray<std::shared_ptr<TComponentType>> myComponents;
};

template <typename TComponentType>
std::shared_ptr<TComponentType> ComponentFactory<TComponentType>::CreateComponent()
{
	myComponents.Add(std::make_shared<TComponentType>());
	return myComponents.GetLast();
}

template <typename TComponentType>
ComponentFactory<TComponentType>::ComponentFactory()
{

}

template <typename TComponentType>
ComponentFactory<TComponentType>::~ComponentFactory()
{

}