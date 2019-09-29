#pragma once
#include "lua.hpp"

class LuaStatic {
public:
	static int errorfunc(lua_State * L);
	static int pantic(lua_State* L);
};