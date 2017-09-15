#ifndef SCRIPTMANAGER_H
#define SCRIPTMANAGER_H

#include <string>
#include <iostream>
#include <stdio.h>
#include <sstream>
#include <list>
#include <vector>

extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}


typedef int(*LuaFunction)(lua_State*);

class ScriptManager
{
public:
	ScriptManager();
	bool LoadScript(const std::string script);
	bool CloseScript();
	template<typename T>
	bool CallEvent(std::string script, const std::string luaevent, std::size_t me, T them);
	bool UpdateScript(std::string script, const std::string luaevent, std::size_t me, float dt);
	void Resume();
	void Reset();
	void AddFunction(std::string const& FunctionName, LuaFunction FunctionPointer);
	void RegisterLUAFunction();

private:
	lua_State* luaState;
	std::list<std::string> loaded_;
	std::string current_Script;
	std::vector<std::pair<std::string, LuaFunction>> luaFunc;

public:
	std::string scriptID_;
};

template<typename T>
bool ScriptManager::CallEvent(std::string script, const std::string luaevent, std::size_t me, T them)
{
	if (script.empty())
	{
		std::cout << "LUA ERROR: Calling event " << luaevent << " on an object that does not exist\n";
		return false;
	}

	lua_getglobal(luaState, script.c_str());
	if (!lua_istable(luaState, -1))
	{
		std::cout << "LUA ERROR: Event " << luaevent << " called on : " << script <<
			" which does not exist.\n";
		lua_pop(luaState, 2);
		return false;
	}
	lua_pushstring(luaState, luaevent.c_str());
	lua_gettable(luaState, -2);

	if (!lua_isfunction(luaState, -1))
	{
		//std::cout << "LUA ERROR: Event " << luaevent << " does not exist for "
		//	<< script << std::endl;
		lua_pop(luaState, 2);
		return false;
	}

	lua_pushnumber(luaState, me);
	lua_pushnumber(luaState, them);

	//std::cout << "Calling " << luaevent << " from " << script << std::endl;
	if (lua_pcall(luaState, 2, 0, 0))
	{
		std::cout << "LUA ERROR: While calling " << luaevent << " on " << script
			<< " - " << lua_tostring(luaState, -1) << std::endl;
		lua_pop(luaState, 2);
		return false;
	}

	return true;
}

ScriptManager* GetScriptManager();



#endif