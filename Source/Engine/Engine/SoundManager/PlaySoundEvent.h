#pragma once

namespace ENGINE_NAMESPACE
{

	struct PlaySoundEvent
	{
		PlaySoundEvent(const char * aSoundEventName) : mySoundEventName(aSoundEventName)
		{}

		const char * mySoundEventName;
	};

}
