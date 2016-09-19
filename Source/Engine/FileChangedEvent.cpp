#include "stdafx.h"
#include "FileChangedEvent.h"

FileChangedEvent::FileChangedEvent(const std::string &aPath)
{
	myPath = aPath;
}

FileChangedEvent::~FileChangedEvent()
{
}
