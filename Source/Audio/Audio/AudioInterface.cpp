#include "AudioInterface.h"
#include "WwiseManager.h"


CAudioInterface* CAudioInterface::myInstance = nullptr;
CAudioInterface::CAudioInterface()
	:myWwiseManager(nullptr)
{
}

CAudioInterface::~CAudioInterface()
{
	delete myWwiseManager;
}

bool CAudioInterface::Init(const char* aInitBank)
{
	myWwiseManager = new CWwiseManager();
	return myWwiseManager->Init(aInitBank);
}

void CAudioInterface::Update()
{
	if (myWwiseManager)
	{
		myWwiseManager->Update();
	}
		
}

bool CAudioInterface::LoadBank(const char* aBankPath)
{
	if (myWwiseManager)
	{
		return myWwiseManager->LoadBank(aBankPath);
	}
	return false;
}

void CAudioInterface::UnLoadBank(const char* aBankPath)
{
	if (myWwiseManager)
	{
		return myWwiseManager->UnLoadBank(aBankPath);
	}
}

void CAudioInterface::PostEvent(const char* aEvent)
{
	if (myWwiseManager)
	{
		return myWwiseManager->PostEvent(aEvent);
	}
}

void CAudioInterface::SetErrorCallBack(callback_function aErrorCallback)
{
	if (myWwiseManager)
	{
		return myWwiseManager->SetErrorCallBack(aErrorCallback);
	}
}