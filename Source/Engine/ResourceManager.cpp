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
	Engine::GetFileWatcher().PostChanges();
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

template <typename TResourceType>
std::shared_ptr<TResourceType>
ResourceManager::Get(const std::string& aPath, LoadError * aError)
{
	LoadedResource * resourceContainer = nullptr;
	std::shared_ptr<TResourceType> resource = nullptr;
	auto &&it = myLoadedResources.find(aPath);

	if (it != myLoadedResources.end())
	{
		resourceContainer = &*it->second;
		resource = std::static_pointer_cast<TResourceType>(resourceContainer->Get());

		// Resource has been unloaded, force reload
		if (resource == nullptr)
		{
			resourceContainer = nullptr;
			myLoadedResources.erase(it);
		}
	}

	if (resourceContainer == nullptr)
	{
		Stopwatch watch;
		LoadError error = LoadError::aSuccess;
		LoadError & errorToSet = aError != nullptr ? *aError : error;
		resource = ResourceLoader<TResourceType>::Load(aPath, errorToSet);

		if (resource == nullptr)
		{
			switch (errorToSet)
			{
			case LoadError::eCorrupted:
				Error(std::string("Could not load resource \"") + aPath + std::string("\". File is corrupted."));
			case LoadError::eNotFound:
				Error(std::string("Could not load resource \"") + aPath + std::string("\". File not found."));
			case LoadError::eWrongType:
				Error(std::string("Could not load resource \"") + aPath + std::string("\". Invalid Type."));
			case LoadError::aSuccess:
				Error(std::string("Could not load resource \"") + aPath + std::string("\". Error not set."));
			default:
				Error(std::string("Could not load resource \"") + aPath + std::string("\". Unknown error (") + std::to_string(static_cast<int>(errorToSet)) + std::string(")."));
			}
		}

		Engine::GetLogger().LogResource("Resource \"{0}\" loaded in {1}ms", aPath, watch.GetElapsedTime().InMilliseconds());

		myLoadedResources.emplace(aPath, std::make_shared<LoadedResource>(resource, aPath));
	}

	return resource;
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
