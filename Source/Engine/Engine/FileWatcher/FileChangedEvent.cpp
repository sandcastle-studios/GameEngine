#include "stdafx.h"
#include "Engine\FileWatcher\FileChangedEvent.h"

FileChangedEvent::FileChangedEvent(const std::string &aPath)
{
	myPath = aPath;
}

FileChangedEvent::~FileChangedEvent()
{
}
