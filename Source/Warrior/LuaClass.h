#pragma once
#include "LuaManager.h"

template<typename T>
class LuaClass
{
private:
	const char* _name;
public:
	LuaClass(const char* name)
	{
		_name = name;
		Singleton<LuaManager>::GetInstance()->ExportClass<T>(name);
	}

	template<typename F> 
	inline LuaClass<T>& DefFunc(const char* funcname, F f)
	{
		Singleton<LuaManager>::GetInstance()->ExportFunc<T, F>(funcname, f);
		return *this;
	}

	template<typename F>
	inline LuaClass<T>& DefGet(const char* propertyname, F f)
	{
		Singleton<LuaManager>::GetInstance()->ExportGet<T, F>(propertyname, f);
		return *this;
	}

	template<typename F>
	inline LuaClass<T>& DefSet(const char* propertyname, F f)
	{
		Singleton<LuaManager>::GetInstance()->ExportSet<T, F>(propertyname, f);
		return *this;
	}

	template<typename F>
	inline LuaClass<T>& DefIndex(F f)
	{
		Singleton<LuaManager>::GetInstance()->ExportIndex<T, F>(f);
		return *this;
	}

	template<typename F>
	inline LuaClass<T>& DefStaticFunc(const char* funcname, F f)
	{
		Singleton<LuaManager>::GetInstance()->ExportFunc(funcname, f);
		return *this;
	}

	void Finish()
	{
		Singleton<LuaManager>::GetInstance()->ExportEnd();
	}

	virtual ~LuaClass()
	{

	}
};