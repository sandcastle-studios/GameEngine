#pragma once
#include <Engine\PostMaster.h>

class CWwiseManager;
namespace ENGINE_NAMESPACE
{

	struct PlaySoundEvent;

	class SoundManger : public Subscriber<PlaySoundEvent>
	{
	public:
		SoundManger();
		~SoundManger();

		bool Init(const char* aInitBank);
		bool LoadBank(const char* aBankPath);
		void UnLoadBank(const char* aBankPath);
		void PostEvent(const char* aEvent);
		void Update();

		/*typedef void(*callback_function)(const char*);
		void SetErrorCallBack(callback_function aErrorCallback);*/

		virtual ReceiveResult Receive(const PlaySoundEvent & aMessage);

	private:
		std::unique_ptr<CWwiseManager> myWwiseManager;

		static void ErrorCallback(const char* aError);
	};

}
