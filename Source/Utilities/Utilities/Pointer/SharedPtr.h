#pragma once

namespace ENGINE_NAMESPACE
{

	template <typename TPointerType>
	class SharedPtr
	{
	public:
		SharedPtr(const SharedPtr &aOtherPointer);
		SharedPtr(SharedPtr && aOtherPointer);
		SharedPtr(TPointerType *aPointer);
		SharedPtr();
		virtual ~SharedPtr();

		SharedPtr & operator=(SharedPtr && aOtherPointer);
		SharedPtr & operator=(const SharedPtr & aOtherPointer);
		bool operator==(std::nullptr_t aNullptr) const;
		bool operator!=(std::nullptr_t aNullptr) const;
		bool operator==(const SharedPtr & aOtherPointer) const;
		bool operator!=(const SharedPtr & aOtherPointer) const;

		unsigned short GetRefCount()const;
		TPointerType *operator->();
		const TPointerType &operator*();

	protected:
		void(*myReturnFunction)(SharedPtr *);

		std::atomic_int *myReferenceCounter;
		TPointerType *myPointer;
	};

	template <typename TPointerType>
	bool SharedPtr<TPointerType>::operator==(const SharedPtr & aOtherPointer) const
	{
		return (myPointer == aOtherPointer.myPointer);
	}

	template <typename TPointerType>
	bool SharedPtr<TPointerType>::operator!=(const SharedPtr & aOtherPointer) const
	{
		return !(myPointer == aOtherPointer.myPointer);
	}

	template <typename TPointerType>
	bool SharedPtr<TPointerType>::operator==(std::nullptr_t aNullptr) const
	{
		return (myPointer == nullptr);
	}

	template <typename TPointerType>
	bool SharedPtr<TPointerType>::operator!=(std::nullptr_t aNullptr) const
	{
		return !(myPointer == nullptr);
	}

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
	SharedPtr<TPointerType>::SharedPtr(const SharedPtr &aOtherPointer)
	{
		myReturnFunction = aOtherPointer.myReturnFunction;
		myReferenceCounter = aOtherPointer.myReferenceCounter;
		if (myReferenceCounter != nullptr)
		{
			myReferenceCounter->fetch_add(1);
		}
		myPointer = aOtherPointer.myPointer;
	}

	template <typename TPointerType>
	SharedPtr<TPointerType>::SharedPtr(SharedPtr && aOtherPointer)
	{
		myPointer = aOtherPointer.myPointer;
		myReferenceCounter = aOtherPointer.myReferenceCounter;
		myReturnFunction = aOtherPointer.myReturnFunction;

		aOtherPointer.myPointer = nullptr;
		aOtherPointer.myReferenceCounter = nullptr;
		aOtherPointer.myReturnFunction = nullptr;
	}

	template <typename TPointerType>
	SharedPtr<TPointerType> & SharedPtr<TPointerType>::operator=(const SharedPtr & aOtherPointer)
	{
		myPointer = aOtherPointer.myPointer;
		myReferenceCounter = aOtherPointer.myReferenceCounter;
		myReturnFunction = aOtherPointer.myReturnFunction;
		if (myReferenceCounter != nullptr)
		{
			myReferenceCounter->fetch_add(1);
		}
		return *this;
	}

	template <typename TPointerType>
	SharedPtr<TPointerType> & SharedPtr<TPointerType>::operator=(SharedPtr && aOtherPointer)
	{
		myPointer = aOtherPointer.myPointer;
		myReferenceCounter = aOtherPointer.myReferenceCounter;
		myReturnFunction = aOtherPointer.myReturnFunction;

		aOtherPointer.myPointer = nullptr;
		aOtherPointer.myReferenceCounter = nullptr;
		aOtherPointer.myReturnFunction = nullptr;
		return *this;
	}

	template <typename TPointerType>
	SharedPtr<TPointerType>::~SharedPtr()
	{
		if (myReferenceCounter != nullptr)
		{
			int count = myReferenceCounter->fetch_sub(1) - 1;

			if (count <= 0)
			{
				myReturnFunction(this);

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

}
