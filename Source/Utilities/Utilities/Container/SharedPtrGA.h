#pragma once

#include "Utilities/Container/GrowingArray.h"

template <typename TPointerType, typename TCountType>
class SharedPtrGA;


template <typename TPointerType, typename TCountType = unsigned short>
class SharedPtrGAContainer
{
public:
	SharedPtrGAContainer(GrowingArray<TPointerType, TCountType> & aGrowingArray);

	void AddPointer(SharedPtrGA<TPointerType, TCountType> & aPointer);
	void RemovePointer(SharedPtrGA<TPointerType, TCountType> & aPointer);

	unsigned short GetRefCount() const;

private:
	GrowingArray<SharedPtrGA<TPointerType, TCountType>*, unsigned short> myPointers;
	GrowingArray<TPointerType, TCountType> & myGrowingArray;

};

template <typename TPointerType, typename TCountType = unsigned short>
SharedPtrGAContainer<TPointerType, TCountType>::SharedPtrGAContainer(GrowingArray<TPointerType, TCountType> & aGrowingArray) : myGrowingArray(aGrowingArray)
{
}

template <typename TPointerType, typename TCountType = unsigned short>
void SharedPtrGAContainer<TPointerType, TCountType>::AddPointer(SharedPtrGA<TPointerType, TCountType> & aPointer)
{
	myPointers.Add(&aPointer);
}

template <typename TPointerType, typename TCountType = unsigned short>
void SharedPtrGAContainer<TPointerType, TCountType>::RemovePointer(SharedPtrGA<TPointerType, TCountType> & aPointer)
{
	myPointers.RemoveCyclic(&aPointer);
}

template <typename TPointerType, typename TCountType = unsigned short>
unsigned short SharedPtrGAContainer<TPointerType, TCountType>::GetRefCount() const
{
	return myPointers.Size();
}

//--------------------------------------------------------------------------------------
//
//
//--------------------------------------------------------------------------------------

template <typename TPointerType, typename TCountType = unsigned short>
class SharedPtrGA
{
public:
	SharedPtrGA(GrowingArray<TPointerType, TCountType> &aGrowingArray,  TPointerType & anElement);
	SharedPtrGA(const SharedPtrGA<TPointerType, TCountType> &aOtherPointer);
	~SharedPtrGA();
	SharedPtrGA();

	unsigned short GetRefCount()const;
	TPointerType *operator->();
private:
	SharedPtrGAContainer<TPointerType, TCountType> * myContainer;
	TPointerType *myPointer;
};

template <typename TPointerType, typename TCountType /*= unsigned short*/>
SharedPtrGA<TPointerType, TCountType>::SharedPtrGA()
{

}

template <typename TPointerType, typename TCountType = unsigned short>
SharedPtrGA<TPointerType, TCountType>::SharedPtrGA(GrowingArray<TPointerType, TCountType> &aGrowingArray,  TPointerType & anElement)
{
	myContainer = new SharedPtrGAContainer<TPointerType, TCountType>(aGrowingArray);
	myContainer->AddPointer(*this);
	myPointer = &anElement;
}

template <typename TPointerType, typename TCountType = unsigned short >
SharedPtrGA<TPointerType, TCountType>::SharedPtrGA(const SharedPtrGA<TPointerType, TCountType> &aOtherPointer) :myContainer(aOtherPointer.myContainer)
{
	myContainer->AddPointer(*this);
	myPointer = aOtherPointer.myPointer;
}

template <typename TPointerType, typename TCountType = unsigned short>
SharedPtrGA<TPointerType, TCountType>::~SharedPtrGA()
{
	myContainer->RemovePointer(*this);
	if (myContainer->GetRefCount() <= 0)
	{
		delete myContainer;
		myContainer = nullptr;
	}
}

template <typename TPointerType, typename TCountType = unsigned short>
unsigned short SharedPtrGA<TPointerType, TCountType>::GetRefCount() const
{
	return myContainer->GetRefCount();
}

template <typename TPointerType, typename TCountType /*= unsigned short*/>
TPointerType * SharedPtrGA<TPointerType, TCountType>::operator->()
{
	return myPointer;
}
