#include "stdafx.h"
#include "Script.h"
#include <lua.hpp>
#include "ScriptFile.h"

Script::Script(lua_State* aState, const std::shared_ptr<ScriptFile>& aScriptFile, int aLuaRef)
{
	L = aState;
	myScriptFile = aScriptFile;
	myLuaRef = aLuaRef;
}

Script::~Script()
{
	luaL_unref(L, LUA_REGISTRYINDEX, myLuaRef);
	myLuaRef = LUA_NOREF;

	myScriptFile->RemoveScript(*this);
}

void Script::UpdateRef(int aLuaRef)
{
	luaL_unref(L, LUA_REGISTRYINDEX, myLuaRef);
	myLuaRef = aLuaRef;
}
