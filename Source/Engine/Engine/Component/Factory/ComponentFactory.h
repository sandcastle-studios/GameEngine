#pragma once
#include <Utilities/Container/GrowingArray.h>
#include "Engine/Component/Factory/BaseComponentFactory.h"
#include <Utilities/Container/SharedPtrGA.h>

template <typename TComponentType>
class ComponentFactory : public BaseComponentFactory
{
public:
	ComponentFactory() {};
	~ComponentFactory() {};

	SharedPtrGA<TComponentType> ComponentFactory<TComponentType>::CreateComponent();
	SharedPtrGA<TComponentType> ComponentFactory<TComponentType>::GetComponent(unsigned short aIndex)const;

	virtual void Update(const Time & aDeltaTime) override;

	virtual void Render() override;

private:
	GrowingArray<TComponentType> myComponents;
};

template <typename TComponentType>
SharedPtrGA<TComponentType> ComponentFactory<TComponentType>::GetComponent(unsigned short aIndex)const
{
	//SharedPtrGA<TComponentType> component(myComponents, myComponents.GetLast());
	return SharedPtrGA<TComponentType> (myComponents, myComponents.GetLast());

	//return SharedPtrGA<TComponentType>(myComponents, myComponents[aIndex]);
}

template <typename TComponentType>
SharedPtrGA<TComponentType> ComponentFactory<TComponentType>::CreateComponent()
{
	myComponents.Add(TComponentType());
	return SharedPtrGA<TComponentType> (myComponents, myComponents.GetLast());
}

template <typename TComponentType>
inline void ComponentFactory<TComponentType>::Update(const Time & aDeltaTime)
{
	for (unsigned short iComponent = 0; iComponent < myComponents.Size(); ++iComponent)
	{
		myComponents[iComponent].Update(aDeltaTime);
	}
}

template <typename TComponentType>
inline void ComponentFactory<TComponentType>::Render()
{
	for (unsigned short iComponent = 0; iComponent < myComponents.Size(); ++iComponent)
	{
		myComponents[iComponent].Render();
	}
}