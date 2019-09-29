// Fill out your copyright notice in the Description page of Project Settings.

#include "LuaManager.h"
#include "FileHelper.h"
#include "PlatformFilemanager.h"
#include "paths.h"
#include "Application.h"
#include "LuaStatic.h"
#include "Logger.h"

template<>
LuaManager* Singleton<LuaManager>::_instance = NULL;

void LuaManager::OnNew()
{
	L = luaL_newstate();
	luaL_openlibs(L);
	lua_atpanic(L, LuaStatic::pantic);
	Application::Export();
	ExportGlobal("_app", *Singleton<Application>::GetInstance());
}

void LuaManager::ExportGlobal(const char * name, ScriptObject & obj)
{
	Write<ScriptObject&>(L, obj);
	lua_setglobal(L, name);
}

uint16 LuaManager::RefObj(ScriptObject& refer, void * refee)
{
	int32 top = lua_gettop(L);
	Write<ScriptObject&>(L, refer);
	lua_pushhead(L, refee);
	int32 pos = lua_tabref(L, -2);
	checkf(sizeof(int32) == sizeof(int), TEXT("int [%d] should be 32 bit[%d]"), sizeof(int32), sizeof(int));
	lua_pop(L, 1);
	checkf(lua_gettop(L) == top, TEXT("stack [%d] must has the same num as before [%d]"), lua_gettop(L), top);
	return pos;
}

void LuaManager::UnrefObj(ScriptObject& refer, int32 pos)
{
	int32 top = lua_gettop(L);
	Write<ScriptObject&>(L, refer);
	//lua_pushhead(L, refee);
	lua_tabunref(L, -1, pos);
	lua_pop(L, 1);
	checkf(lua_gettop(L) == top, TEXT("stack [%d] must has the same num as before [%d]"), lua_gettop(L), top);
}

void LuaManager::DoString(FString content, FString chunk)
{
	if (luaL_loadbuffer(L, TCHAR_TO_UTF8(*content), (uint64)(content.GetCharArray().Num()), TCHAR_TO_UTF8(*chunk)))
	{
		LogError("[Lua][DoString.luaL_loadbuffer]%s", *Read<FString>(L,-1));
		return;
	}
	if (!lua_pcall(L, 0, -1, 0))
		LogError("[Lua][DoString.lua_pcall]%s", *Read<FString>(L, -1));
	//todo
	//返回值数组
}

void LuaManager::DoFile(FString path)
{
	IPlatformFile& file = FPlatformFileManager::Get().GetPlatformFile();
	FString abpath = FPaths::ProjectContentDir() + path;
	TArray<uint8> content;
	if (!FFileHelper::LoadFileToArray(content, *abpath))
	{
		LogError("[Lua][DoFile.LoadFileToArray]%s", *abpath);
		return;
	}
	lua_pushcclosure(L, LuaStatic::errorfunc, 0);
	if (luaL_loadbuffer(L, (const char*)(content.GetData()), (uint64)content.Num(), TCHAR_TO_UTF8(*path)))
	{
		LogError("[Lua][DoFile.luaL_loadbuffer]%s", *Read<FString>(L, -1));
		return;
	}
	if (lua_pcall(L, 0, -1, -2))
		LogError("[Lua][DoFile.lua_pcall]%s", *Read<FString>(L, -1));
	//todo
	//返回值数组
}

LuaManager::~LuaManager()
{
	lua_close(L);
	L = NULL;
}
