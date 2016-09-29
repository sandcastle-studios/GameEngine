#include "WwiseManager.h"

#include "include\AK\SoundEngine\Common\AkTypes.h"
#include "include\AK\Tools\Common\AkPlatformFuncs.h"
#include "include\AK\SoundEngine\Common\AkSoundEngine.h"

#include "include\AK\SoundEngine\Common\AkMemoryMgr.h"		// Memory Manager
#include "include\AK\SoundEngine\Common\AkModule.h"		// Default memory and stream managers
#include "include\AK\SoundEngine\Common\IAkStreamMgr.h"		// Streaming Manager
#include "include\AK\SoundEngine\Common\AkSoundEngine.h"    // Sound engine
#include "include\AK\MusicEngine\Common\AkMusicEngine.h"	// Music Engine
#include "include\AK\SoundEngine\Common\AkStreamMgrModule.h"	// AkStreamMgrModule
#include "include\AK\Plugin\AllPluginsRegistrationHelpers.h"	// Plug-ins
#include "include\AK\Comm\AkCommunication.h"	// Plug-ins
#include "SoundEngine\Win32\AkFilePackageLowLevelIOBlocking.h"




#define GAME_OBJECT_POSTEST 100
#define DEMO_DEFAULT_POOL_SIZE 2*1024*1024
#define DEMO_LENGINE_DEFAULT_POOL_SIZE 2*1024*1024

namespace AK
{
	void * AllocHook(size_t in_size)
	{
		return malloc(in_size);
	}
	void FreeHook(void * in_ptr)
	{
		free(in_ptr);
	}
	void * VirtualAllocHook(
		void * in_pMemAddress,
		size_t in_size,
		DWORD in_dwAllocationType,
		DWORD in_dwProtect
		)
	{
		return VirtualAlloc(in_pMemAddress, in_size, in_dwAllocationType, in_dwProtect);
	}
	void VirtualFreeHook(
		void * in_pMemAddress,
		size_t in_size,
		DWORD in_dwFreeType
		)
	{
		VirtualFree(in_pMemAddress, in_size, in_dwFreeType);
	}
}

namespace AK_HELPER
{
	/// Returns the number of elements in an array
	template <class T, size_t N> AkForceInline size_t AK_ARRAYSIZE(T(&)[N])
	{
		return N;
	}
}

CAkFilePackageLowLevelIOBlocking* m_pLowLevelIO;
CWwiseManager::CWwiseManager()
	:myErrorCallbck(nullptr)
{
	myIsInitialized = false;
}


CWwiseManager::~CWwiseManager()
{
	if (myIsInitialized == true)
	{
		AK::SoundEngine::StopAll();
		AK::SoundEngine::UnregisterGameObj(GAME_OBJECT_POSTEST);
		AK::SoundEngine::ClearBanks();
		TermWwise();
	}
}

bool CWwiseManager::Init(const char* aInitBank)
{
	myIsInitialized = true;
	AkMemSettings memSettings;
	AkStreamMgrSettings stmSettings;
	AkDeviceSettings deviceSettings;
	AkInitSettings initSettings;
	AkPlatformInitSettings platformInitSettings;
	AkMusicSettings musicInit;

	memSettings.uMaxNumPools = 20;
	AK::StreamMgr::GetDefaultSettings(stmSettings);

	AK::StreamMgr::GetDefaultDeviceSettings(deviceSettings);

	AK::SoundEngine::GetDefaultInitSettings(initSettings);
	initSettings.uDefaultPoolSize = DEMO_DEFAULT_POOL_SIZE;

	AK::SoundEngine::GetDefaultPlatformInitSettings(platformInitSettings);
	platformInitSettings.uLEngineDefaultPoolSize = DEMO_LENGINE_DEFAULT_POOL_SIZE;

	AK::MusicEngine::GetDefaultInitSettings(musicInit);

	platformInitSettings.hWnd = GetActiveWindow();

	// Initialize Wwise
	AkOSChar szError[500];
	bool bSuccess = InitWwise(memSettings, stmSettings, deviceSettings, initSettings, platformInitSettings, musicInit, szError, (unsigned int)AK_HELPER::AK_ARRAYSIZE(szError));
	if (!bSuccess)
	{
		return false;
	}

	AkBankID bankIDInit;
	if (AK::SoundEngine::LoadBank(aInitBank, AK_DEFAULT_POOL_ID, bankIDInit) != AK_Success)
	{
		return false;
	}

	AK::SoundEngine::RegisterGameObj(GAME_OBJECT_POSTEST, "Positioning Demo");
	return true;
}

void CWwiseManager::Update()
{
	AK::SoundEngine::RenderAudio();
}


bool CWwiseManager::LoadBank(const char* aBankPath)
{
	AkBankID bankID; // Not used
	if (AK::SoundEngine::LoadBank(aBankPath, AK_DEFAULT_POOL_ID, bankID) != AK_Success)
	{
		char buffer[50];
		sprintf_s(buffer, "Could not find %s!", aBankPath);

		CallError(buffer);
		//SetLoadFileErrorMessage("Positioning_Demo.bnk");
		return false;
	}
	return true;
}


void CWwiseManager::UnLoadBank(const char* aBankPath)
{
	AK::SoundEngine::UnloadBank(aBankPath, nullptr);
}


void CWwiseManager::PostEvent(const char* aEvent)
{
	AK::SoundEngine::PostEvent(aEvent, GAME_OBJECT_POSTEST);
}

bool CWwiseManager::InitWwise(AkMemSettings &in_memSettings, AkStreamMgrSettings &in_stmSettings, AkDeviceSettings &in_deviceSettings, AkInitSettings &in_initSettings, AkPlatformInitSettings &in_platformInitSettings, AkMusicSettings &in_musicInit, AkOSChar* in_szErrorBuffer, unsigned int in_unErrorBufferCharCount)
{
	m_pLowLevelIO = new CAkFilePackageLowLevelIOBlocking();
	//
	// Create and initialize an instance of the default memory manager. Note
	// that you can override the default memory manager with your own. Refer
	// to the SDK documentation for more information.
	//

	AKRESULT res = AK::MemoryMgr::Init(&in_memSettings);
	if (res != AK_Success)
	{
		CallError("Momory manager could not init!");
		return false;
	}

	//
	// Create and initialize an instance of the default streaming manager. Note
	// that you can override the default streaming manager with your own. Refer
	// to the SDK documentation for more information.
	//

	// Customize the Stream Manager settings here.

	if (!AK::StreamMgr::Create(in_stmSettings))
	{
		CallError("Stream manager could not init!");
		return false;
	}

	// 
	// Create a streaming device with blocking low-level I/O handshaking.
	// Note that you can override the default low-level I/O module with your own. Refer
	// to the SDK documentation for more information.        
	//

	// CAkFilePackageLowLevelIOBlocking::Init() creates a streaming device
	// in the Stream Manager, and registers itself as the File Location Resolver.
	res = m_pLowLevelIO->Init(in_deviceSettings);
	if (res != AK_Success)
	{
		CallError("Low level IO could not init!");
		return false;
	}

	//
	// Create the Sound Engine
	// Using default initialization parameters
	//

	res = AK::SoundEngine::Init(&in_initSettings, &in_platformInitSettings);
	if (res != AK_Success)
	{
		CallError("Sound engine could not init!");
		return false;
	}

	//
	// Initialize the music engine
	// Using default initialization parameters
	//

	res = AK::MusicEngine::Init(&in_musicInit);
	if (res != AK_Success)
	{
		CallError("Music engine could not init!");
		return false;
	}

#ifdef _DEBUG
#if !defined AK_OPTIMIZED && !defined INTEGRATIONDEMO_DISABLECOMM
	//
	// Initialize communications (not in release build!)
	//
	AkCommSettings commSettings;
	AK::Comm::GetDefaultInitSettings(commSettings);
	res = AK::Comm::Init(commSettings);
	if (res != AK_Success)
	{
		CallError("AkCommSettings error!");
	}
#endif // AK_OPTIMIZED
#endif

	//
	// Register plugins
	/// Note: This a convenience method for rapid prototyping. 
	/// To reduce executable code size register/link only the plug-ins required by your game 
	res = AK::SoundEngine::RegisterAllPlugins();
	if (res != AK_Success)
	{
		CallError("Plugins could not register!");
	}

	return true;
}

void CWwiseManager::TermWwise()
{
#ifdef _DEBUG
#if !defined AK_OPTIMIZED && !defined INTEGRATIONDEMO_DISABLECOMM
	// Terminate communications between Wwise and the game
	AK::Comm::Term();
#endif // AK_OPTIMIZED
#endif
	// Terminate the music engine
	AK::MusicEngine::Term();

	// Terminate the sound engine
	if (AK::SoundEngine::IsInitialized())
	{
		AK::SoundEngine::Term();
	}

	// Terminate the streaming device and streaming manager
	// CAkFilePackageLowLevelIOBlocking::Term() destroys its associated streaming device 
	// that lives in the Stream Manager, and unregisters itself as the File Location Resolver.
	if (AK::IAkStreamMgr::Get())
	{
		m_pLowLevelIO->Term();
		AK::IAkStreamMgr::Get()->Destroy();
	}

	// Terminate the Memory Manager
	if (AK::MemoryMgr::IsInitialized())
	{
		AK::MemoryMgr::Term();
	}
}

void CWwiseManager::SetErrorCallBack(callback_function aErrorCallback)
{
	myErrorCallbck = aErrorCallback;
}

void CWwiseManager::CallError(const char* aError)
{
	if (myErrorCallbck)
	{
		myErrorCallbck(aError);
	}
}