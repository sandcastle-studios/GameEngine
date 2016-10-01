#pragma once

struct lua_State;
class ScriptFile;

class Script
{
public:
	Script(lua_State * aState, const std::shared_ptr<ScriptFile> & aScriptFile, int aLuaRef);
	~Script();

	void UpdateRef(int aLuaRef);

private:
	std::shared_ptr<ScriptFile> myScriptFile;
	lua_State * L;
	int myLuaRef;
};

