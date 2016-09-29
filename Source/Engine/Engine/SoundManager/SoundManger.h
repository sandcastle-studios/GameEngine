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

private:
	std::unique_ptr<CWwiseManager> myWwiseManager;

	static void ErrorCallback(const char* aError);
};