#pragma once
#include "Engine/Component/Factory/BaseComponentFactory.h"

template <typename TPointerType>
class SharedPtrComponent;

template <typename TComponentType>
class ComponentFactory : public BaseComponentFactory
{
public:
	ComponentFactory();
	~ComponentFactory();

	SharedPtrComponent<TComponentType> CreateComponent();
	//SharedPtrComponent<TComponentType> ComponentFactory<TComponentType>::GetComponent(unsigned short aIndex);

	virtual void Update(const Time & aDeltaTime) override;

	virtual void Render() override;

	virtual void ReturnMemory(unsigned short aIndex) override;

private:
	unsigned short GetAndActivateIndex();

	GrowingArray<bool> myComponentsActiveTag;
	GrowingArray<TComponentType> myComponents;
	Stack<unsigned short> myFreeMemorySlots;
};

#include "Engine\Component\Pointer\SharedPtrComponent.h"

template <typename TComponentType>
ComponentFactory<TComponentType>::~ComponentFactory()
{

}

template <typename TComponentType>
ComponentFactory<TComponentType>::ComponentFactory()
{
	unsigned short numberOfElements = 1024;
	myComponents.Resize(numberOfElements);
	myComponentsActiveTag.Resize(numberOfElements);
	for (unsigned short i = 0; i < numberOfElements; i++)
	{
		myFreeMemorySlots.Push(i);
		myComponentsActiveTag[i] = false;
	}
}

template <typename TComponentType>
void ComponentFactory<TComponentType>::ReturnMemory(unsigned short aIndex)
{
	myComponents[aIndex].Destruct();
	myFreeMemorySlots.Push(aIndex);
	myComponentsActiveTag[aIndex] = false;
}

//emplate <typename TComponentType>
//haredPtrComponent<TComponentType> ComponentFactory<TComponentType>::GetComponent(unsigned short aIndex)
//
//	if (myComponentsActiveTag[aIndex] == false)
//	{
//		Engine::GetLogger().LogError("Component Error, tried to access an INACTIVE component with GetComponent() from factory");
//	}
//	return SharedPtrComponent<TComponentType> (this, aIndex, myComponents[aIndex]);
//

template <typename TComponentType>
SharedPtrComponent<TComponentType> ComponentFactory<TComponentType>::CreateComponent()
{
	unsigned short index = GetAndActivateIndex();
	myComponents[index].Construct();
	return SharedPtrComponent<TComponentType>(this, index, &myComponents[index]);
}

template <typename TComponentType>
inline void ComponentFactory<TComponentType>::Update(const Time & aDeltaTime)
{
	for (unsigned short iComponent = 0; iComponent < myComponents.Size(); ++iComponent)
	{
		if (myComponentsActiveTag[iComponent] == true)
		{
			myComponents[iComponent].Update(aDeltaTime);
		}
	}
}

template <typename TComponentType>
inline void ComponentFactory<TComponentType>::Render()
{
	for (unsigned short iComponent = 0; iComponent < myComponents.Size(); ++iComponent)
	{
		if (myComponentsActiveTag[iComponent] == true)
		{
			myComponents[iComponent].Render();
		}
	}
}


template <typename TComponentType>
unsigned short ComponentFactory<TComponentType>::GetAndActivateIndex()
{
	unsigned short index = myFreeMemorySlots.Pop();
	myComponentsActiveTag[index] = true;
	return index;
}
