#pragma once
#include "Luahelper.h"

#define LuaActionHead( n,p,m ) \
template<p(n)>\
struct LuaAction m(n) :LuaRef{\
	using LuaRef::LuaRef;\
	void operator()(TTN(n))\
	{\
		if(IsNull()) return;\
		lua_State* L = Singleton<LuaManager>::GetInstance( )->L;\
		lua_pushhead(L, obj);\

#define LuaActionTail(n) \
	;lua_pcall(L, n, 0, 0);\
	}\
};

#define LUAACTION(n) LuaActionHead(n, TNN, NTN) WN(n) LuaActionTail(n)
#define LUAACTIONMAX(n) LuaActionHead(n, TNND, MTN) WN(n) LuaActionTail(n)

LUAACTIONMAX(10)
LUAACTION(9)
LUAACTION(8)
LUAACTION(7)
LUAACTION(5)
LUAACTION(4)
LUAACTION(3)
LUAACTION(2)
LUAACTION(1)
LUAACTION(0)