#pragma once

class DXRenderer;
class FileChangeWatcher;
class ResourceManager;
class DebugLogger;
class Debugger;

class Engine
{
public:
	static DXRenderer & GetRenderer();
	static FileChangeWatcher & GetFileWatcher();
	static ResourceManager & GetResourceManager();
	static DebugLogger & GetLogger();
	static Debugger & GetDebugger();

	static void CreateInstance();
	static Engine & GetInstance();
	static void DestroyInstance();

	void AttachDebugger(const std::shared_ptr<Debugger> & aDebugger);

private:
	Engine();
	~Engine();

	std::unique_ptr<DXRenderer> myRenderer;
	FileChangeWatcher * myFileWatcher;
	std::unique_ptr<ResourceManager> myResourceManager;
	std::unique_ptr<DebugLogger> myDebugLogger;
	std::shared_ptr<Debugger> myDebugger;

	static Engine * ourInstance;
};

inline Engine & Engine::GetInstance()
{
	assert("Engine not created" && ourInstance != nullptr);
	return *ourInstance;
}

inline DXRenderer & Engine::GetRenderer(){
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

inline Debugger & Engine::GetDebugger()
{
	if (GetInstance().myDebugger == nullptr)
	{
		Error("No debugger is attached!");
	}
	return *GetInstance().myDebugger;
}
