#include "stdafx.h"
#include "Engine\FileChanger\FileChangedEvent.h"

FileChangedEvent::FileChangedEvent(const std::string &aPath)
{
	myPath = aPath;
}

FileChangedEvent::~FileChangedEvent()
{
}
