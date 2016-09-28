#pragma once

class DXRenderer;
class FileChangeWatcher;
class ResourceManager;
class DebugLogger;
class LightLoader;

class Engine
{
public:
	static DXRenderer & GetRenderer();
	static FileChangeWatcher & GetFileWatcher();
	static ResourceManager & GetResourceManager();
	static DebugLogger & GetLogger();
	static LightLoader & GetLightLoader();

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
	std::unique_ptr<LightLoader> myLightLoader;

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

inline LightLoader& Engine::GetLightLoader()
{
	return *GetInstance().myLightLoader;
}
