#include "stdafx.h"
#include "ResourceManager.h"
#include "FileChangeWatcher.h"

ResourceManager::ResourceManager()
{
}


ResourceManager::~ResourceManager()
{
}

void ResourceManager::Update()
{
	std::string changedFile;
	while (Engine::GetFileWatcher().QueryFileChanges(changedFile))
	{
		auto &&it = myLoadedResources.find(changedFile);

		if (it != myLoadedResources.end())
		{
			it->second->Get()->Reload();
		}
	}
}

Resource::Resource(const std::string & aFilePath)
{
	myPath = aFilePath;
}

Resource::~Resource()
{
}

const std::string & Resource::GetPath() const
{
	return myPath;
}

LoadedResource::LoadedResource(const std::shared_ptr<Resource>& aResource, const std::string& aPath)
{
	myResource = aResource;
}

std::shared_ptr<Resource> LoadedResource::Get()
{
	if (myResource.expired())
		return nullptr;
	return myResource.lock();
}
