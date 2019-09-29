// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
/**
 * 
 */
class WARRIOR_API LuaRef
{
protected:
	void* obj;
public:
	int32 pos;
	void* GetPtr();
public:
	LuaRef() :LuaRef(0) {}
	LuaRef(void* obj );
	bool IsNull();
	~LuaRef();
};
