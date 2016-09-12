#pragma once
#include "Size.h"

enum class WindowMessageType
{
	eUnknown,
	eCloseButtonPressed,
	eResizeBegins,
	eResizeEnds,
	eSizeChanged,
	ePaint,
	eCreate,
	eDestroy,

	eCount
};

struct SizeChangedData
{
	Size<int> newSize;
};
