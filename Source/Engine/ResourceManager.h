#pragma once
#include "FileChangedEvent.h"

enum class LoadError
{
	aSuccess,
	eNotFound,
	eWrongType,
	eCorrupted
};

class Resource
{
public:
	virtual ~Resource();

	virtual void Reload() = 0;
	const std::string & GetPath() const;

protected:
	Resource(const std::string & aFilePath);

private:
	std::string myPath;
};

template<typename TResourceType>
class ResourceLoader
{
public:
	static std::shared_ptr<TResourceType> Load(const std::string & aPath, LoadError & aError);
};

class LoadedResource
{
public:
	LoadedResource(const std::shared_ptr<Resource> & aResource, const std::string &  aPath);
	
	std::shared_ptr<Resource> Get();

private:
	std::weak_ptr<Resource> myResource;
};

class ResourceManager : public Subscriber<FileChangedEvent>
{
public:
	ResourceManager();
	~ResourceManager();
	void Update();
	template <typename TResourceType>
	std::shared_ptr<TResourceType> Get(const std::string &aPath, LoadError * aError = nullptr);

	ReceiveResult Receive(const FileChangedEvent& aMessage) override;

private:
	std::unordered_map<std::string, std::shared_ptr<LoadedResource>> myLoadedResources;
};

template <typename TResourceType>
std::shared_ptr<TResourceType> ResourceLoader<TResourceType>::Load(const std::string& aPath, LoadError& aError)
{
	static_assert(false, "The resource loader for this type does not exist or was not included!");
}

template <typename TResourceType>
std::shared_ptr<TResourceType> ResourceManager::Get(const std::string& aPath, LoadError * aError)
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
