#pragma once

class DXRenderer;
class FileChangeWatcher;

class Engine
{
public:
	DXRenderer & GetRenderer();
	FileChangeWatcher & GetFileWatcher();

	static void CreateInstance();
	static Engine & GetInstance();
	static void DestroyInstance();

private:
	Engine();
	~Engine();

	std::unique_ptr<DXRenderer> myRenderer;
	std::unique_ptr<FileChangeWatcher> myFileWatcher;

	static Engine * ourInstance;
};

inline Engine & Engine::GetInstance()
{
	assert("Engine not created" && ourInstance != nullptr);
	return *ourInstance;
}

inline DXRenderer & Engine::GetRenderer()
{
	return *myRenderer;
}

inline FileChangeWatcher & Engine::GetFileWatcher()
{
	return *myFileWatcher;
}
