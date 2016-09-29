#pragma once

class CWwiseManager;

class SoundManger
{
public:
	SoundManger();
	~SoundManger();

	bool Init(const char* aInitBank);
	bool LoadBank(const char* aBankPath);
	void UnLoadBank(const char* aBankPath);
	void PostEvent(const char* aEvent);
	void Update();

	typedef void(*callback_function)(const char*);
	void SetErrorCallBack(callback_function aErrorCallback);

private:
	std::unique_ptr<CWwiseManager> myWwiseManager;
};