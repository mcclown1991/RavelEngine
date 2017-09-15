#include "ScriptManager.h"
#include "assert.h"
#include "Factory.h"
#include "GameObject.h"

extern void RegisterFunctions(lua_State* L);
static ScriptManager instance;

ScriptManager* GetScriptManager()
{
	return &instance;
}

ScriptManager::ScriptManager()
{
	/* initialize Lua */
	luaState = lua_open();

	/* load Lua base libraries */
	luaL_openlibs(luaState);

	RegisterFunctions(luaState);
}

void ScriptManager::RegisterLUAFunction() {
	for (auto& item : luaFunc) {
		lua_register(luaState, item.first.c_str(), item.second);
	}
}

bool ScriptManager::LoadScript(const std::string script)
{
	std::list<std::string>::iterator itr = std::find(loaded_.begin(), loaded_.end(), script);

	if (itr != loaded_.end()) {
		return true;
	}
	// Update Script Manager currently loaded scriptID //
	this->scriptID_ = script;

	std::string scriptPath = script;

	if (luaL_dofile(luaState, scriptPath.c_str()))
	{
		std::cout << "LUA ERROR: Could not load file " << script << std::endl;
		return false;
	}

	loaded_.push_back(script);
	std::cout << "LUA: " << script << " loaded." << std::endl;
	return true;
}



bool ScriptManager::UpdateScript(std::string script, const std::string luaevent, std::size_t me, float dt)
{
	//script = "Resources/Script/" + script;
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
		std::cout << "LUA ERROR: Event " << luaevent << " does not exist for "
		<< script << std::endl;
		lua_pop(luaState, 2);
		return false;
	}

	lua_pushnumber(luaState, me);
	lua_pushnumber(luaState, dt);

	if (lua_pcall(luaState, 2, 0, 0))
	{
		std::cout << "LUA ERROR: While calling " << luaevent << " on " << script
			<< " - " << lua_tostring(luaState, -1) << std::endl;
		lua_pop(luaState, 2);
		return false;
	}

	return true;
}

void ScriptManager::Resume()
{
	lua_resume(luaState, 0);
}

void ScriptManager::Reset()
{
	lua_close(luaState);
	luaState = lua_open();
	luaL_openlibs(luaState);
	loaded_.clear();
	RegisterFunctions(luaState);
}

void ScriptManager::AddFunction(std::string const& FunctionName, LuaFunction FunctionPointer) {
	luaFunc.push_back(std::make_pair(FunctionName, FunctionPointer));
}