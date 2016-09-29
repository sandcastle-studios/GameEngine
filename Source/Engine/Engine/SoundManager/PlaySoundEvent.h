#pragma once

struct PlaySoundEvent
{
	PlaySoundEvent(const char * aSoundEventName) : mySoundEventName(aSoundEventName)
	{}

	const char * mySoundEventName;
};