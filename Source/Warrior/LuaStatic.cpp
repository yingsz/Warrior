#include "LuaStatic.h"
#include "Luahelper.h"
#include "Logger.h"

int LuaStatic::errorfunc(lua_State *L) {
	lua_getglobal(L, "debug");
	lua_getfield(L, -1, "traceback");
	lua_remove(L, -2);
	lua_pushvalue(L, 1);
	lua_pushnumber(L, 2);
	lua_call(L, 2, 1);
	return 1;
}

int LuaStatic::pantic(lua_State * L)
{
	FString err = Read<FString>(L, -1);
	LogFatal("[LuaException]%s", *err);
	return 0;
}
