#pragma once
#include <Utilities/Pointer/SharedPtr.h>

#include "Engine/Component/Factory/ComponentFactory.h"

template <typename TPointerType>
class SharedPtrComponent : public SharedPtr<TPointerType>
{
public:
	SharedPtrComponent();
	SharedPtrComponent(BaseComponentFactory * aComponentFactory, unsigned short aComponentIndex, TPointerType *aPointer);

	template <typename TOldPointerType>
	static SharedPtrComponent<TPointerType> CastFrom(const SharedPtrComponent<TOldPointerType> & aOtherPtr);

protected:
	virtual void Return() override final;

private:
	template<typename T>
	friend class SharedPtrComponent;

	BaseComponentFactory * myComponentFactory;
	unsigned short myComponentIndex;
};

template <typename TPointerType>
SharedPtrComponent<TPointerType>::SharedPtrComponent()
{
}

template <typename TPointerType>
template <typename TOldPointerType>
SharedPtrComponent<TPointerType> SharedPtrComponent<TPointerType>::CastFrom(const SharedPtrComponent<TOldPointerType> & aOtherPtr)
{
	SharedPtrComponent newPtr;
	newPtr.myReferenceCounter = aOtherPtr.myReferenceCounter;
	newPtr.myReferenceCounter->fetch_add(1);
	newPtr.myPointer = static_cast<TPointerType*>(aOtherPtr.myPointer);
	newPtr.myComponentFactory = static_cast<BaseComponentFactory*>(aOtherPtr.myComponentFactory);
	newPtr.myComponentIndex = aOtherPtr.myComponentIndex;
	return newPtr;
}


template <typename TPointerType>
SharedPtrComponent<TPointerType>::SharedPtrComponent(BaseComponentFactory * aComponentFactory, unsigned short aComponentIndex, TPointerType *aPointer) : SharedPtr(aPointer)
{
	myComponentFactory = aComponentFactory;
	myComponentIndex = aComponentIndex;
}

template <typename TPointerType>
void SharedPtrComponent<TPointerType>::Return()
{
	myComponentFactory->ReturnMemory(myComponentIndex);
}
