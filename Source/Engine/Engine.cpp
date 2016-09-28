#include "stdafx.h"
#include "Engine.h"
#include "DXRenderer.h"
#include "FileChangeWatcher.h"
#include "LightLoader.h"

Engine * Engine::ourInstance = nullptr;

Engine::Engine()
{
	myRenderer = std::make_unique<DXRenderer>();
	myFileWatcher = std::make_unique<FileChangeWatcher>();
	myResourceManager = std::make_unique<ResourceManager>();
	myDebugLogger = std::make_unique<DebugLogger>();
	myLightLoader = std::make_unique<LightLoader>();
}

Engine::~Engine()
{
}

void Engine::CreateInstance()
{
	assert("Instance already created" && ourInstance == nullptr);

	ourInstance = new Engine();
}

void Engine::DestroyInstance()
{
	assert("Instance not created" && ourInstance != nullptr);

	delete ourInstance;
	ourInstance = nullptr;
}
