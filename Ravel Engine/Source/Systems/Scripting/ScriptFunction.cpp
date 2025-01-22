#include "ScriptManager.h"

/* THE FOUR GOLDEN RULES WHEN EDITING THIS FILE
*
* 1. Every function will follow this prototype:
*       int funcname(lua_State* L)
*
* 2. Maintain the integrity of the lua stack. Don't leak!
*
* 3. Add your function to RegisterFunctions() or it won't be recognised.
*    RegisterFunctions() must ALWAYS be the last function in this file
*
* 4. Every function must have Doxygen compliant documentation
*    describing what it does ad what its parameters are
*/

/** This function should move obj to position
*
* @param
* @return
*/
int DebugLog(lua_State * L)
{
	std::string msg = luaL_checkstring(L, -2);
	auto arg = luaL_checknumber(L, -1);

	lua_pop(L, 2);

#ifdef _DEBUG
	std::cout << msg << " " << arg << std::endl;
//#else
	//UNREFERENCED_PARAMETER(msg);
	//UNREFERENCED_PARAMETER(arg);
#endif
	return 0;
}

void RegisterFunctions(lua_State* L) {
	lua_register(L, "DebugLog", DebugLog);
}