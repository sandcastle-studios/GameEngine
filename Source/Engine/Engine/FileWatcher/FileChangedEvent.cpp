#include "stdafx.h"
#include "Engine\FileWatcher\FileChangedEvent.h"

namespace ENGINE_NAMESPACE
{
	FileChangedEvent::FileChangedEvent(const std::string &aPath)
	{
		myPath = aPath;
	}

	FileChangedEvent::~FileChangedEvent()
	{
	}
}
