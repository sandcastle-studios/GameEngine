#pragma once
#include "WindowMessageType.h"

union WindowMessageData
{
	SizeChangedData resizeEvent;
	KeyData keyEvent;

	inline WindowMessageData();
	inline ~WindowMessageData();
};

inline WindowMessageData::WindowMessageData()
{
	memset(this, 0, sizeof(*this));
}

inline WindowMessageData::~WindowMessageData()
{
}

struct WindowMessage
{
	WindowMessageType type;
	WindowMessageData data;
};
