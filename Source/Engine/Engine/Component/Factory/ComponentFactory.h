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

	virtual void Update(const Time & aDeltaTime) override;

	virtual void Render() override;

	virtual void ReturnMemory(unsigned short aIndex) override;

	template <typename TEnumerator>
	void EnumerateActiveComponents(const TEnumerator & aEnumerator);

private:
	unsigned short GetAndActivateIndex();

	GrowingArray<bool> myComponentsActiveTag;
	GrowingArray<TComponentType> myComponents;
	Stack<unsigned short> myFreeMemorySlots;
};

template <typename TComponentType>
template <typename TEnumerator>
void ComponentFactory<TComponentType>::EnumerateActiveComponents(const TEnumerator & aEnumerator)
{
	for (unsigned short iComponent = 0; iComponent < myComponents.Size(); ++iComponent)
	{
		if (myComponentsActiveTag[iComponent] == true)
		{
			aEnumerator(myComponents[iComponent]);
		}
	}
}

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
	Engine::GetLogger().LogInfo("Index {0} returned to factory.", aIndex);

	myComponents[aIndex].Destruct();
	myComponents[aIndex].~TComponentType();
	myFreeMemorySlots.Push(aIndex);
	myComponentsActiveTag[aIndex] = false;
}

template <typename TComponentType>
SharedPtrComponent<TComponentType> ComponentFactory<TComponentType>::CreateComponent()
{
	unsigned short index = GetAndActivateIndex();
	new (&myComponents[index]) TComponentType();
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
