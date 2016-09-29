#include "stdafx.h"
#include "SoundManger.h"
#include "Audio/WwiseManager.h"
#include "Engine/SoundManager/PlaySoundEvent.h"

SoundManger::SoundManger()
{
	myWwiseManager = std::make_unique<CWwiseManager>();
}

SoundManger::~SoundManger()
{
}

bool SoundManger::Init(const char* aInitBank)
{
	return myWwiseManager->Init(aInitBank);
}

void SoundManger::Update()
{
	myWwiseManager->Update();
}

bool SoundManger::LoadBank(const char* aBankPath)
{
	return myWwiseManager->LoadBank(aBankPath);
}

void SoundManger::UnLoadBank(const char* aBankPath)
{
	return myWwiseManager->UnLoadBank(aBankPath);
}

void SoundManger::PostEvent(const char* aEvent)
{
	return myWwiseManager->PostEvent(aEvent);
}

void SoundManger::SetErrorCallBack(callback_function aErrorCallback)
{
	return myWwiseManager->SetErrorCallBack(aErrorCallback);
}

ReceiveResult SoundManger::Receive(const PlaySoundEvent & aMessage)
{
	PostEvent(aMessage.mySoundEventName);

	return ReceiveResult::eContinue;
}
