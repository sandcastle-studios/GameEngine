#pragma once
#include <Utilities/Container/GrowingArray.h>
#include "Engine/Component/Factory/BaseComponentFactory.h"

template <typename TComponentType>
class ComponentFactory : public BaseComponentFactory
{
public:
	ComponentFactory();
	~ComponentFactory();

private:
	GrowingArray<TComponentType> myComponents;
};

template <typename TComponentType>
ComponentFactory<TComponentType>::ComponentFactory()
{

}

template <typename TComponentType>
ComponentFactory<TComponentType>::~ComponentFactory()
{

}