#pragma once

class DXRenderer;
class FileChangeWatcher;
class ResourceManager;
class DebugLogger;

class Engine
{
public:
	static DXRenderer & GetRenderer();
	static FileChangeWatcher & GetFileWatcher();
	static ResourceManager & GetResourceManager();
	static DebugLogger & GetLogger();

	static void CreateInstance();
	static Engine & GetInstance();
	static void DestroyInstance();

private:
	Engine();
	~Engine();

	std::unique_ptr<DXRenderer> myRenderer;
	std::unique_ptr<FileChangeWatcher> myFileWatcher;
	std::unique_ptr<ResourceManager> myResourceManager;
	std::unique_ptr<DebugLogger> myDebugLogger;

	static Engine * ourInstance;
};

inline Engine & Engine::GetInstance()
{
	assert("Engine not created" && ourInstance != nullptr);
	return *ourInstance;
}

inline DXRenderer & Engine::GetRenderer()
{
	return *GetInstance().myRenderer;
}

inline FileChangeWatcher & Engine::GetFileWatcher()
{
	return *GetInstance().myFileWatcher;
}

inline ResourceManager& Engine::GetResourceManager()
{
	return *GetInstance().myResourceManager;
}

inline DebugLogger& Engine::GetLogger()
{
	return *GetInstance().myDebugLogger;
}
