#include "stdafx.h"
#include <assert.h>
#include <iostream>
#include <stack>
#include <memory>
#include <dxgi.h>
#include <d3d11.h>
#include <vector>

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
	virtual void Activate() = 0
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

	BindingContext(BindingContext & aCopy)
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

class PipelineWrapper;

template <typename TFunctionSignature, typename TState>
class PipelineFunction : public IPipelineFunction
{
public:
	PipelineFunction(PipelineWrapper & aWrapper, d3dcontext * aContext, TFunctionSignature aFunction)
	{
		myContext = aContext;
		myFunction = aFunction;
		myIsModified = false;
		myWrapper = &aWrapper;
	}

	~PipelineFunction()
	{
	}
	
	PipelineFunction & Push(const TState & aState)
	{
		if (memcmp(&myCurrentState, &aState, sizeof(aState)) != 0)
		{
			QueueModification();
		}
		myStateStack.push(aState);
		return *this;
	}

	void Pop() override final
	{
		TState oldState = myStateStack.top();
		myStateStack.pop();
		if (memcmp(&myStateStack.top(), &oldState, sizeof(oldState)) != 0)
		{
			QueueModification();
		}
	}

	void Activate() override final
	{
		myIsModified = false;
		auto && state = myStateStack.top();
		if (memcmp(&state, &myCurrentState, sizeof(state)) != 0)
		{
			myCurrentState = state;
			myCurrentState.Activate(myContext, myFunction);
		}
	}
	
private:
	void QueueModification()
	{
		if (myIsModified == false)
		{
			myWrapper->QueueModification(*this);
			myIsModified = true;
		}
	}

	std::stack<TState> myStateStack;
	TState myCurrentState;
	d3dcontext * myContext;
	TFunctionSignature myFunction;
	PipelineWrapper * myWrapper;
	bool myIsModified;
};


struct BindShaderResourceData
{
	typedef int(d3dcontext::*FunctionSignature)(int);

	int index;

	BindShaderResourceData() {}
	BindShaderResourceData(int aIndex) { index = aIndex; }

	void Activate(d3dcontext * aContext, FunctionSignature aSignature) const
	{
		int returnValue = ((*aContext).*(aSignature))(index);
		// Check return for error
	}
};

using BindShaderResourceFunction = PipelineFunction<BindShaderResourceData::FunctionSignature, BindShaderResourceData>;

class PipelineWrapper
{
public:
	PipelineWrapper(d3dcontext * context)
		: myBindToPS(*this, context, &d3dcontext::BindToPS),
		myBindToVS(*this, context, &d3dcontext::BindToVS)
	{
	}

	void Draw()
	{
		InvokeChanges();
	}

	void Dispatch()
	{
		InvokeChanges();
	}

	ReturnContainer BindToVS(int aSlot)
	{
		return myBindToVS.Push(BindShaderResourceData(aSlot));
	}

	ReturnContainer BindToPS(int aSlot)
	{
		return myBindToPS.Push(BindShaderResourceData(aSlot));
	}

	void QueueModification(IPipelineFunction & aFunction)
	{
		myChangedFunctions.push_back(&aFunction);
	}

private:
	void InvokeChanges()
	{
		for (size_t i=0; i<myChangedFunctions.size(); i++)
		{
			myChangedFunctions[i]->Activate();
		}
		myChangedFunctions.clear();
	}

	std::vector<IPipelineFunction*> myChangedFunctions;

	BindShaderResourceFunction myBindToPS;
	BindShaderResourceFunction myBindToVS;
};

int main()
{
	d3dcontext context;
	PipelineWrapper pipeline(&context);

	BindingContext ba = pipeline.BindToPS(1);
	BindingContext ba2 = pipeline.BindToVS(2);

	pipeline.Draw();

	{
		BindingContext b = pipeline.BindToPS(4);
		BindingContext b2 = pipeline.BindToVS(3);
		pipeline.Draw();

		BindingContext b3 = pipeline.BindToPS(4);
		BindingContext b4 = pipeline.BindToVS(3);
	}

	pipeline.Draw();

	std::cin.get();
    return 0;
}

