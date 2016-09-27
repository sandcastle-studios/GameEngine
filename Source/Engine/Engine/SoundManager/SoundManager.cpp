#include "stdafx.h"
#include "SoundManager.h"
#include "Audio\WwiseManager.h"

SoundManager::SoundManager()
	:myWwiseManager(nullptr)
{
}

SoundManager::~SoundManager()
{
	delete myWwiseManager;
}

bool SoundManager::Init(const char* aInitBank)
{
	myWwiseManager = new CWwiseManager();
	return myWwiseManager->Init(aInitBank);
}

void SoundManager::Update()
{
	if (myWwiseManager)
	{
		myWwiseManager->Update();
	}
		
}

bool SoundManager::LoadBank(const char* aBankPath)
{
	if (myWwiseManager)
	{
		return myWwiseManager->LoadBank(aBankPath);
	}
	return false;
}

void SoundManager::UnLoadBank(const char* aBankPath)
{
	if (myWwiseManager)
	{
		return myWwiseManager->UnLoadBank(aBankPath);
	}
}

void SoundManager::PostEvent(const char* aEvent)
{
	if (myWwiseManager)
	{
		return myWwiseManager->PostEvent(aEvent);
	}
}

void SoundManager::SetErrorCallBack(callback_function aErrorCallback)
{
	if (myWwiseManager)
	{
		return myWwiseManager->SetErrorCallBack(aErrorCallback);
	}
}