#pragma once

template <typename TPointerType>
class SharedPtr
{
public:
	SharedPtr(const SharedPtr<TPointerType> &aOtherPointer);
	SharedPtr(TPointerType *aPointer);
	SharedPtr();
	virtual ~SharedPtr();

	unsigned short GetRefCount()const;
	TPointerType *operator->();
	const TPointerType &operator*();

	// SharedPtr<PlayerComponent>::CastFrom(ptr);

	//template <typename TOldPointerType>
	//static SharedPtr<TPointerType> CastFrom(const SharedPtr<TOldPointerType> & aOtherPtr);

protected:
	virtual void Return() = 0;

	std::atomic_int *myReferenceCounter;
	TPointerType *myPointer;
};

template <typename TPointerType>
void SharedPtr<TPointerType>::Return()
{
}

//template <typename TPointerType>
//template <typename TOldPointerType>
//SharedPtr<TPointerType> SharedPtr<TPointerType>::CastFrom(const SharedPtr<TOldPointerType> & aOtherPtr)
//{
//	SharedPtr newPtr;
//	newPtr.myReferenceCounter = aOtherPtr.myReferenceCounter;
//	newPtr.myReferenceCounter->fetch_add(1);
//	newPtr.myPointer = static_cast<TPointerType>(aOtherPtr.myPointer);
//	return newPtr;
//}

template <typename TPointerType>
SharedPtr<TPointerType>::SharedPtr(TPointerType *aPointer)
{
	myReferenceCounter = new std::atomic_int(1);
	myPointer = aPointer;
}

template <typename TPointerType>
SharedPtr<TPointerType>::SharedPtr()
{
	myReferenceCounter = nullptr;
	myPointer = nullptr;
}

template <typename TPointerType>
SharedPtr<TPointerType>::SharedPtr(const SharedPtr<TPointerType> &aOtherPointer)
{
	myReferenceCounter = aOtherPointer.myReferenceCounter;
	if (myReferenceCounter != nullptr)
	{
		myReferenceCounter->fetch_add(1);
	}
	myPointer = aOtherPointer.myPointer;
}

template <typename TPointerType>
SharedPtr<TPointerType>::~SharedPtr()
{
	if (myReferenceCounter != nullptr)
	{
		if (myReferenceCounter->fetch_sub(1) <= 0)
		{
			Return();
			myPointer->Destruct();

			delete myReferenceCounter;
			myReferenceCounter = nullptr;
		}
	}
}

template <typename TPointerType>
unsigned short SharedPtr<TPointerType>::GetRefCount() const
{
	if (myReferenceCounter != nullptr)
	{
		return myContainer->GetRefCount();
	}
	return 0;
}

template <typename TPointerType>
TPointerType * SharedPtr<TPointerType>::operator->()
{
	return myPointer;
}

template <typename TPointerType>
const TPointerType & SharedPtr<TPointerType>::operator*()
{
	return *myPointer;
}
