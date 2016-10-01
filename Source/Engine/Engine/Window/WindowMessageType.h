#pragma once
#include "Engine\Size.h"

namespace ENGINE_NAMESPACE
{
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
		eKeyDown,
		eKeyUp,

		eCount,
	};

	struct SizeChangedData
	{
		Size<int> newSize;
	};

	struct KeyData
	{
		KeyboardKey key;
		int repeatCount;
	};
}
