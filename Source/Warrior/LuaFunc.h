#pragma once
#include "LuaDefine.h"
#include "LuaRef.h"

#define LuaFuncHead( n,p,m ) \
template<p(V,n)>\
struct LuaFunc m(V,n):LuaRef {\
		using LuaRef:LuaRef;\
	V operator()(TTN(n))\
	{\
		lua_State* L = Singleton<LuaManager>::GetInstance( )->L;\
		lua_pushhead(L, obj);\

#define LuaFuncTail(n) \
	;lua_call(L, n, 1);\
	return Read<V>(L, -1);\
	}\
};

#define LUAFUNC(n) LuaFuncHead(n, TNNH, VTNH) WN(n) LuaFuncTail(n)
#define LUAFUNCMAX(n) LuaFuncHead(n, TNNHD, MVTNH) WN(n) LuaFuncTail(n)

LUAFUNCMAX(10)
LUAFUNC(9)
LUAFUNC(8)
LUAFUNC(7)
LUAFUNC(6)
LUAFUNC(5)
LUAFUNC(4)
LUAFUNC(3)
LUAFUNC(2)
LUAFUNC(1)