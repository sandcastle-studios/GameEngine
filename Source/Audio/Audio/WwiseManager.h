#pragma once

#include "..\Wwise\include\AK\SoundEngine\Common\AkTypes.h"
#include "..\Wwise\include\AK\Tools\Common\AkPlatformFuncs.h"
#include "..\Wwise\include\AK\SoundEngine\Common\AkSoundEngine.h"

#include "..\Wwise\include\AK\SoundEngine\Common\AkMemoryMgr.h"		// Memory Manager
#include "..\Wwise\include\AK\SoundEngine\Common\AkModule.h"		// Default memory and stream managers
#include "..\Wwise\include\AK\SoundEngine\Common\IAkStreamMgr.h"		// Streaming Manager
#include "..\Wwise\include\AK\SoundEngine\Common\AkSoundEngine.h"    // Sound engine
#include "..\Wwise\include\AK\MusicEngine\Common\AkMusicEngine.h"	// Music Engine
#include "..\Wwise\include\AK\SoundEngine\Common\AkStreamMgrModule.h"	// AkStreamMgrModule
#include "..\Wwise\include\AK\Plugin\AllPluginsRegistrationHelpers.h"	// Plug-ins
#include "..\Wwise\include\AK\Comm\AkCommunication.h"	// Plug-ins
#include "SoundEngine\Win32\AkFilePackageLowLevelIOBlocking.h"

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
	void TermWwise();
	bool InitWwise(AkMemSettings &in_memSettings, AkStreamMgrSettings &in_stmSettings, AkDeviceSettings &in_deviceSettings, AkInitSettings &in_initSettings, AkPlatformInitSettings &in_platformInitSettings, AkMusicSettings &in_musicInit, AkOSChar* in_szErrorBuffer, unsigned int in_unErrorBufferCharCount);
	void CallError(const char* aError);
	callback_function myErrorCallbck;
};
