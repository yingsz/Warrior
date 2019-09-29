#pragma once
#include "ScriptObject.h"
#include "LuaClass.h"

class TestClass : public  ScriptObject 
{
public: 
	const char* GetName() { return SCRIPTNAEM(TestClass); }
	uint16 GetMeta() { return ClassIndex<TestClass>::GetIndex( ); }
	//static void Func1(int a) {}
	void Func1(int a) {}
	static void Export()
	{
		_SCRIPT_DEF_BEGIN( TestClass )
			_SCRIPT_DEF_FUNC( Func1 )
		_SCRIPT_DEF_FINISH( )
	}
public:
	TestClass();
	virtual ~TestClass();

SCRIPTCLASSEND