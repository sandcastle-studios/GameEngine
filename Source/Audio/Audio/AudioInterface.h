#pragma once
#include <functional>   // std::bind

class CWwiseManager;
class CAudioInterface
{
public:
	static CAudioInterface* GetInstance(){ return myInstance; }
	static void CreateInstance(){ myInstance = new CAudioInterface(); }
	static void Destroy(){ delete myInstance; myInstance = nullptr; }

	bool Init(const char* aInitBank);
	bool LoadBank(const char* aBankPath);
	void UnLoadBank(const char* aBankPath);
	void PostEvent(const char* aEvent);
	void Update();

	typedef void(*callback_function)(const char*);
	void SetErrorCallBack(callback_function aErrorCallback);
private:
	static CAudioInterface* myInstance;
	CAudioInterface();
	~CAudioInterface();

	CWwiseManager* myWwiseManager;
};

