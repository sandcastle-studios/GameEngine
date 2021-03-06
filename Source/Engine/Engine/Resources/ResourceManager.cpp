#include "stdafx.h"
#include "Engine\Resources\ResourceManager.h"
#include "Engine\FileWatcher\FileChangeWatcher.h"

namespace ENGINE_NAMESPACE
{

	ResourceManager::ResourceManager()
	{
	}


	ResourceManager::~ResourceManager()
	{
	}

	void ResourceManager::Update()
	{
	}

	ReceiveResult ResourceManager::Receive(const FileChangedEvent & aMessage)
	{
		auto &&it = myLoadedResources.find(aMessage.GetPath());

		if (it != myLoadedResources.end())
		{
			it->second->Get()->Reload();
		}

		return ReceiveResult::eContinue;
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
}

