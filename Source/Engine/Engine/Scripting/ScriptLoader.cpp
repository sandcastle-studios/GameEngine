#include "stdafx.h"
#include "ScriptLoader.h"
#include "ScriptFile.h"
#include <lua.hpp>

lua_State * MakeState()
{
	lua_State * l = luaL_newstate();
	luaL_openlibs(l);
	return l;
}

lua_State * L = MakeState();

namespace ENGINE_NAMESPACE
{

	std::shared_ptr<ScriptFile> ResourceLoader<ScriptFile>::Load(const std::string& aPath, LoadError& aError)
	{
		std::shared_ptr<ScriptFile> file = std::make_shared<ScriptFile>(L, aPath);
		file->myOurSelf = file;
		return file;
	}

}