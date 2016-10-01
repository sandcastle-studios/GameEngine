#pragma once
#include "Engine/Resources/ResourceManager.h"

struct lua_State;
class Script;

class ScriptFile : public Resource
{
public:
	ScriptFile(lua_State * aState, const std::string & aPath);
	~ScriptFile();

	std::shared_ptr<Script> Execute();
	void Reload() override;
	void RemoveScript(Script & aScript);
	
private:
	friend class ResourceLoader<ScriptFile>;

	int ExecuteAndGetRef();
	
	std::weak_ptr<ScriptFile> myOurSelf;

	lua_State * L;
	GrowingArray<Script*> myScripts;
	int myFunctionReference;
};

