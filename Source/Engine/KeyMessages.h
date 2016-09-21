#pragma once

template <KeyboardKey TKey = KeyboardKey::eNone> 
struct KeyDownMessage
{
	KeyDownMessage(KeyboardKey aKey)
	{
		key = aKey;
	}

	KeyboardKey key;
};

using AnyKeyDownMessage = KeyDownMessage<>;

template <KeyboardKey TKey = KeyboardKey::eNone>
struct KeyRepeatMessage
{
	KeyRepeatMessage(KeyboardKey aKey, int aRepeatCount)
	{
		key = aKey;
		repeatCount = aRepeatCount;
		isFirstRepeat = repeatCount == 0;
	}

	KeyboardKey key;
	int repeatCount;
	bool isFirstRepeat;
};

using AnyKeyRepeatMessage = KeyRepeatMessage<>;

template <KeyboardKey TKey = KeyboardKey::eNone>
struct KeyUpMessage
{
	KeyUpMessage(KeyboardKey aKey)
	{
		key = aKey;
	}

	KeyboardKey key;
};

using AnyKeyUpMessage = KeyUpMessage<>;
