#pragma once



struct AkMemSettings;
struct AkStreamMgrSettings;
struct AkDeviceSettings;
struct AkInitSettings;
struct AkPlatformInitSettings;
struct AkMusicSettings;
typedef wchar_t			AkOSChar;				///< Generic character string


class CWwiseManager
{
public:
	CWwiseManager();
	~CWwiseManager();
	bool Init(const char* aInitBank);
	void Update();
	bool LoadBank(const char* aBankPath);
	void UnLoadBank(const char* aBankPath);
	void PostEvent(const char* aEvent);

	typedef void(*callback_function)(const char*);
	void SetErrorCallBack(callback_function aErrorCallback);
private:
	bool myIsInitialized;
	void TermWwise();
	bool InitWwise(AkMemSettings &in_memSettings, AkStreamMgrSettings &in_stmSettings, AkDeviceSettings &in_deviceSettings, AkInitSettings &in_initSettings, AkPlatformInitSettings &in_platformInitSettings, AkMusicSettings &in_musicInit, AkOSChar* in_szErrorBuffer, unsigned int in_unErrorBufferCharCount);
	void CallError(const char* aError);
	callback_function myErrorCallbck;
};

