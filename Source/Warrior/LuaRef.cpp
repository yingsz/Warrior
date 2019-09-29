// Fill out your copyright notice in the Description page of Project Settings.


#include "LuaRef.h"
#include "UObject/ConstructorHelpers.h"

LuaRef::LuaRef(void* obj)
{
	this->pos = 0;
	this->obj = obj;
	//UE_LOG(LogTemp, Warning, TEXT("LuaRef[%p]", obj);
}

bool LuaRef::IsNull()
{
	return !obj;
}

void * LuaRef::GetPtr()
{
	return obj;
}

LuaRef::~LuaRef()
{
	//UE_LOG(LogTemp, Warning, TEXT("~LuaRef[%p]", obj);
}