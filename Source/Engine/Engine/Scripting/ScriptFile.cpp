#include "stdafx.h"
#include "ScriptFile.h"
#include <lua.hpp>
#include "Script.h"
#include <fstream>

std::string ReadFile(const char * aFile)
{
	std::ifstream t(aFile);
	std::string str;

	t.seekg(0, std::ios::end);
	str.reserve(t.tellg());
	t.seekg(0, std::ios::beg);

	str.assign((std::istreambuf_iterator<char>(t)),
		std::istreambuf_iterator<char>());

	return str;
}

void stackDump(lua_State *L) {
	int i;
	int top = lua_gettop(L);
	for (i = 1; i <= top; i++) {  /* repeat for each level */
		int t = lua_type(L, i);
		switch (t) {

		case LUA_TSTRING:  /* strings */
			printf("`%s'", lua_tostring(L, i));
			break;

		case LUA_TBOOLEAN:  /* booleans */
			printf(lua_toboolean(L, i) ? "true" : "false");
			break;

		case LUA_TNUMBER:  /* numbers */
			printf("%g", lua_tonumber(L, i));
			break;

		default:  /* other values */
			printf("%s", lua_typename(L, t));
			break;

		}
		printf("  ");  /* put a separator */
	}
	printf("\n");  /* end the listing */
}

ScriptFile::ScriptFile(lua_State * aState, const std::string & aPath)
	: Resource(aPath)
{
	L = aState;
	myFunctionReference = LUA_NOREF;

	Reload();
}

ScriptFile::~ScriptFile()
{
	luaL_unref(L, LUA_REGISTRYINDEX, myFunctionReference);
	myFunctionReference = LUA_NOREF;
}

std::shared_ptr<Script> ScriptFile::Execute()
{
	std::shared_ptr<Script> script = std::make_shared<Script>(L, myOurSelf.lock(), ExecuteAndGetRef());
	myScripts.Add(&*script);
	return script;
}

void ScriptFile::Reload()
{
	luaL_unref(L, LUA_REGISTRYINDEX, myFunctionReference);
	myFunctionReference = LUA_NOREF;

	std::string ourFunction = "local self = {  }; ";
	ourFunction += ReadFile(GetPath().c_str());
	ourFunction += "\n\nreturn self";

	if (luaL_loadstring(L, ourFunction.c_str()) != 0)
	{
		Engine::GetLogger().LogError("Could not load file {0}: {1}", GetPath(), lua_tostring(L, -1));
		return;
	}

	if (lua_isfunction(L, -1))
	{
		myFunctionReference = luaL_ref(L, LUA_REGISTRYINDEX);
	}
	else
	{
		Error(FormatString("Unknown type: {0}", lua_typename(L, -1)));
	}

	for (unsigned short i=0; i<myScripts.Size(); i++)
	{
		myScripts[i]->UpdateRef(ExecuteAndGetRef());
	}
}

void ScriptFile::RemoveScript(Script& aScript)
{
	myScripts.RemoveCyclic(&aScript);
}

int ScriptFile::ExecuteAndGetRef()
{
	lua_rawgeti(L, LUA_REGISTRYINDEX, myFunctionReference);

	if (lua_pcall(L, 0, 1, 0) != 0)
	{
		Engine::GetLogger().LogError("Lua runtime error in file {0}: {1}", GetPath(), lua_tostring(L, -1));
		lua_pop(L, 1);
		return LUA_NOREF;
	}

	return luaL_ref(L, LUA_REGISTRYINDEX);
}
