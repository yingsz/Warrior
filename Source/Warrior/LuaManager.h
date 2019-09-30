// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Singleton.h"
#include "ScriptObject.h"
#include "LuaHelper.h"
#include "lua.hpp"
#define _SCRIPT_DEF_BEGIN( x )				LuaClass< x >( "_"#x )
#define _SCRIPT_DEF_NEW( )					.DefConstructor(0)
#define _SCRIPT_DEF_NEW1( T1 )				.DefConstructor(1, TypeContainer<T1>)
#define _SCRIPT_DEF_NEW2( T1,T2 )			.DefConstructor(2, TypeContainer<T1,T2>)
#define _SCRIPT_DEF_NEW3( T1, T2, T3)		.DefConstructor(3, TypeContainer<T1,T2,T3>)
#define _SCRIPT_DEF_NEW4( T1, T2, T3, T4)	.DefConstructor(4, TypeContainer<T1,T2,T3,T4>)
#define _SCRIPT_DEF_FUNC( x )				.DefFunc(#x, &##x)
#define _SCRIPT_DEF_GET( x )				.DefGet( #x, &##x##_get )
#define _SCRIPT_DEF_SET( x )				.DefSet( #x, &##x##_set )
#define _SCRIPT_DEF_SETGET( x )				.DefGet( #x, &##x##_get ).DefSet( #x, &##x##_set )

#define _SCRIPT_DEF_FINISH( )				.Finish( );
template<typename T>
struct ClassIndex
{
	static uint16 GetIndex(uint16 index = 0)
	{
		static uint16 temp = 0;
		if (index != 0)
			temp = index;
		return temp;
	}
};

class WARRIOR_API LuaManager : ISingleton
{
	friend class Singleton<LuaManager>;
public:
	lua_State* L;
	virtual void OnNew();
	template<class T>
	void ExportClass(const char * name)
	{
		int top = lua_gettop(L);
		const char* luaclass =
#include "LuaClass.lua"
			;
		luaL_dostring(L, luaclass);
		top = lua_gettop(L);
		check(lua_gettop(L) == 1);

		Write(L, "__tostring");
		lua_pushcfunction(L, stringfunc);
		lua_settable(L, -3);

		Write(L, "__gc");
		lua_pushcfunction(L, gcfunc);
		lua_settable(L, -3);

		lua_pushvalue(L, -1);
		lua_setglobal(L, name);
		top = lua_gettop(L);
		lua_pushvalue(L, -1);
		ClassIndex<T>::GetIndex(luaL_ref(L, LUA_REGISTRYINDEX));
		top = lua_gettop(L);
		check(lua_gettop(L) == 1);
	}
	
	template<typename T, typename F>
	void ExportConstructor(int argn, F f)
	{
		int top = lua_gettop(L);
		lua_rawgeti(L, LUA_REGISTRYINDEX, ClassIndex<T>::GetIndex());
		checkf(lua_gettop(L) == top + 1, TEXT("top[%d] not expetced [%d]"), lua_gettop(L), top + 1);
		Write(L, "New");
		lua_rawget(L, -2);
		if (lua_isnil(L, -1))
		{
			lua_pop(L, 2);
			for (int i = 1;i < 10;i++)
				Write(L);
			lua_pushcclosure(L, newfunc, 10);
			Write(L, "New");
			lua_pushvalue(L, -2);
			lua_settable(L, -4);
		}
		else
			lua_remove(L, -2);
		new(lua_newuserdata(L, sizeof(F))) F(f);
		Write(L, f);
		lua_setupvalue(L, -2, argn+1);
		checkf(lua_gettop(L) == top + 2, TEXT("top[%d] not expetced [%d]"), lua_gettop(L), top + 1);
		lua_pop(L, 2);
	}

	template<typename T, typename F>
	void ExportFunc(const char * funcname, F f) 
	{
		lua_rawgeti(L, LUA_REGISTRYINDEX, ClassIndex<T>::GetIndex());
		Write(L, funcname);
		new(lua_newuserdata(L, sizeof(F))) F(f);
		Write(L, f);
		lua_settable(L, -3);
		lua_pop(L, 1);
		check(lua_gettop(L) == 1);
	}

	template<typename T, typename F>
	void ExportGet(const char * propertyname, F f)
	{
		int top = lua_gettop(L);
		lua_rawgeti(L, LUA_REGISTRYINDEX, ClassIndex<T>::GetIndex());
		checkf(lua_gettop(L) == top + 1, TEXT("top[%d] not expetced [%d]"), lua_gettop(L), top + 1);
		Write(L, "__index");
		lua_rawget(L, -2);
		checkf(lua_gettop(L) == top + 3, TEXT("top[%d] not expetced [%d]"), lua_gettop(L), top + 1);
		lua_getupvalue(L, -1, 1);//getters
		checkf(lua_gettop(L) == top + 4, TEXT("top[%d] not expetced [%d]"), lua_gettop(L), top + 1);
		Write(L, propertyname);
		new(lua_newuserdata(L, sizeof(F))) F(f);
		Write(L, f);
		lua_settable(L, -3);
		checkf(lua_gettop(L) == top + 4, TEXT("top[%d] not expetced [%d]"), lua_gettop(L), top + 1);
		lua_pop(L, 4);
	}

	template<typename T, typename F>
	void ExportSet(const char * propertyname, F f)
	{
		int top = lua_gettop(L);
		lua_rawgeti(L, LUA_REGISTRYINDEX, ClassIndex<T>::GetIndex());
		checkf(lua_gettop(L) == top + 1, TEXT("top[%d] not expetced [%d]"), lua_gettop(L), top + 1);
		Write(L, "__index");
		lua_rawget(L, -2);
		checkf(lua_gettop(L) == top + 3, TEXT("top[%d] not expetced [%d]"), lua_gettop(L), top + 1);
		lua_getupvalue(L, -1, 2);//setters
		checkf(lua_gettop(L) == top + 4, TEXT("top[%d] not expetced [%d]"), lua_gettop(L), top + 1);
		Write(L, propertyname);
		new(lua_newuserdata(L, sizeof(F))) F(f);
		Write(L, f);
		lua_settable(L, -3);
		checkf(lua_gettop(L) == top + 4, TEXT("top[%d] not expetced [%d]"), lua_gettop(L), top + 1);
		lua_pop(L, 4);
	}

	template<typename T, typename F>
	void ExportIndex(const char * propertyname, F f)
	{
		int top = lua_gettop(L);
		lua_rawgeti(L, LUA_REGISTRYINDEX, ClassIndex<T>::GetIndex());
		checkf(lua_gettop(L) == top + 1, TEXT("top[%d] not expetced [%d]"), lua_gettop(L), top + 1);
		Write(L, "__index");
		lua_rawget(L, -2);
		checkf(lua_gettop(L) == top + 3, TEXT("top[%d] not expetced [%d]"), lua_gettop(L), top + 1);
		new(lua_newuserdata(L, sizeof(F))) F(f);
		Write(L, f);
		lua_setupvalue(L, -2, 3);//indexfunc
		lua_pop(L, 4);
	}

	void ExportEnd()
	{
		lua_pop(L, 1);
	}

	void ExportGlobal(const char* name, ScriptObject& obj);
	uint16 RefObj(ScriptObject& refer, void* refee);
	void UnrefObj(ScriptObject& refer, int32 pos);
	void DoString(FString content, FString chunke);
	void DoFile(FString name);
	virtual~LuaManager();
};
