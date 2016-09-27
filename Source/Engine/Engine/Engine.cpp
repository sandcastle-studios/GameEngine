#include "stdafx.h"
#include "Engine\Engine.h"
#include "Engine\Rendering\DXRenderer.h"
#include "Engine\FileWatcher\FileChangeWatcher.h"
#include "Debugging\Debugger.h"
#include <lua.hpp>

Engine * Engine::ourInstance = nullptr;

Engine::Engine()
{
	lua_State * L = luaL_newstate();
	luaL_openlibs(L);
	luaL_loadfile(L, "test.lua");
	if (lua_isfunction(L, -1))
	{
		if (lua_pcall(L, 0, 0, 0) != 0)
		{
			std::cout << "pcall error: " << lua_tostring(L, -1) << std::endl;
		}
	}
	else if (lua_isstring(L, -1))
	{
		std::cout << lua_tostring(L, -1) << std::endl;
	}
	lua_close(L);

	myRenderer = std::make_unique<DXRenderer>();
	myFileWatcher = new FileChangeWatcher();
	myResourceManager = std::make_unique<ResourceManager>();
	myDebugLogger = std::make_unique<DebugLogger>();
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

void Engine::AttachDebugger(const std::shared_ptr<Debugger> & aDebugger)
{
	myDebugger = aDebugger;
}
