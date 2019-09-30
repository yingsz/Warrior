#pragma once
#include "LuaRef.h"

#define SCRIPTNAEM(name) "_"#name
#define SCRIPTCLASS(name, ...) class name : public  ScriptObject, ##__VA_ARGS__\
{\
public: \
const char* GetName(){ return SCRIPTNAEM(name);}\
uint16 GetMeta() { return ClassIndex<name>::GetIndex();}

#define SCRIPTCLASSEND };

#define SAFE_ASSIGN(a, b) UnrefObject(a);\
a = (b);\
RefObject(b);

class ScriptObject
{
public:
	void* _ptr;
public:
	ScriptObject();
	virtual const char* GetName() = 0;
	virtual uint16 GetMeta() = 0;
	virtual const TCHAR* ToString();
protected:
	void RefObject(LuaRef&);
	void UnrefObject(LuaRef&);
public:
	virtual ~ScriptObject();
};

