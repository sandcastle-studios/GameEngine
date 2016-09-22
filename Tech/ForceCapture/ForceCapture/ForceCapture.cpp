#include "stdafx.h"
#include <assert.h>
#include <iostream>
#include <stack>
#include <memory>

struct d3dcontext
{
	int BindToPS(int aIndex) { std::cout << "Binding index " << aIndex << " to PS" << std::endl; return 0; }
	int BindToVS(int aIndex) { std::cout << "Binding index " << aIndex << " to VS" << std::endl; return 0; }
};

class IPipelineFunction
{
public:
	virtual ~IPipelineFunction()
	{
	}
	virtual void Pop() = 0
	{
	}
};

class BindingContext
{
public:
	BindingContext(IPipelineFunction & aFunction)
	{
		myFunction = &aFunction;
	}

	BindingContext(BindingContext && aCopy)
	{
		myFunction = aCopy.myFunction;
		aCopy.myFunction = nullptr;
	}

	~BindingContext()
	{
		if (myFunction != nullptr)
		{
			myFunction->Pop();
		}
	}

private:
	IPipelineFunction * myFunction;
};

class ReturnContainer
{
public:
	ReturnContainer(IPipelineFunction & aFunction)
	{
		myFunction = &aFunction;
		myIsRead = false;
	}
	ReturnContainer(const ReturnContainer & aCopy) = delete;
	ReturnContainer & operator=(const ReturnContainer & aCopy) = delete;
	
	~ReturnContainer()
	{
		assert(myIsRead == true);
	}

	operator BindingContext()
	{
		assert(myIsRead == false);
		myIsRead = true;
		return BindingContext(*myFunction);
	}

private:
	IPipelineFunction * myFunction;
	bool myIsRead;
};

template <typename TFunctionSignature, typename TState>
class PipelineFunction : public IPipelineFunction
{
public:
	PipelineFunction(d3dcontext * aContext, TFunctionSignature aFunction)
	{
		myContext = aContext;
		myFunction = aFunction;
		myStateStack = new std::stack<TState>();
	}

	~PipelineFunction()
	{
		delete myStateStack;
		myStateStack = nullptr;
	}
	
	template <typename ...TArgs>
	ReturnContainer operator()(const TArgs & ...args)
	{
		Push(TState(args...));
		return *this;
	}

	void Push(const TState & aState)
	{
		if (myStateStack->empty() == false)
		{
			if (memcmp(&myStateStack->top(), &aState, sizeof(aState)) != 0)
			{
				aState.Activate(myContext, myFunction);
			}
		}
		else
		{
			aState.Activate(myContext, myFunction);
		}
		myStateStack->push(aState);
	}

	void Pop() override final
	{
		auto previousState = myStateStack->top();
		myStateStack->pop();

		if (myStateStack->empty() == false)
		{
			if (memcmp(&myStateStack->top(), &previousState, sizeof(previousState)) != 0)
			{
				myStateStack->top().Activate(myContext, myFunction);
			}
		}
	}
	
private:
	d3dcontext * myContext;
	TFunctionSignature myFunction;
	std::stack<TState> * myStateStack;
};


struct BindShaderResourceData
{
	typedef int(d3dcontext::*FunctionSignature)(int);

	int index;

	BindShaderResourceData(int aIndex)
	{
		index = aIndex;
	}

	void Activate(d3dcontext * aContext, FunctionSignature aSignature) const
	{
		((*aContext).*(aSignature))(index);
	}
};

using BindShaderResourceFunction = PipelineFunction<BindShaderResourceData::FunctionSignature, BindShaderResourceData>;

class PipelineWrapper
{
public:
	PipelineWrapper(d3dcontext * context)
		: BindToPS(context, &d3dcontext::BindToPS),
		BindToVS(context, &d3dcontext::BindToVS)
	{
	}

	BindShaderResourceFunction BindToPS;
	BindShaderResourceFunction BindToVS;
};

int main()
{
	d3dcontext context;
	PipelineWrapper pipeline(&context);

	BindingContext ba = pipeline.BindToPS(0);
	BindingContext ba2 = pipeline.BindToVS(0);

	{
		BindingContext b = pipeline.BindToPS(BindShaderResourceData());
		BindingContext b2 = pipeline.BindToVS(2);

		BindingContext b3 = pipeline.BindToPS(1);
		pipeline.BindToVS(2);

	}

	std::cin.get();
    return 0;
}

