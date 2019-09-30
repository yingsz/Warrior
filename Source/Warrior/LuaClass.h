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

	inline LuaClass<T>& DefConstructor(int argn)
	{
		Singleton<LuaManager>::GetInstance()->ExportConstructor<T>(argn, Constructor<T>::Invoke);
		return *this;
	}

	template<typename T1>
	inline LuaClass<T>& DefConstructor(int argn, Constructor<T1>)
	{
		Singleton<LuaManager>::GetInstance()->ExportConstructor<T>(argn, Constructor<T,T1>::Invoke);
		return *this;
	}

	template<typename T1, typename T2>
	inline LuaClass<T>& DefConstructor(int argn, Constructor<T1,T2>)
	{
		Singleton<LuaManager>::GetInstance()->ExportConstructor<T>(argn, Constructor<T, T1,T2>::Invoke);
		return *this;
	}

	template<typename T1, typename T2, typename T3>
	inline LuaClass<T>& DefConstructor(int argn, Constructor<T1, T2, T3>)
	{
		Singleton<LuaManager>::GetInstance()->ExportConstructor<T>(argn, Constructor<T, T1,T2,T3>::Invoke);
		return *this;
	}

	template<typename T1, typename T2, typename T3, typename T4>
	inline LuaClass<T>& DefConstructor(int argn, Constructor<T1, T2, T3,T4>)
	{
		Singleton<LuaManager>::GetInstance()->ExportConstructor<T>(argn, Constructor<T, T1, T2, T3,T4>::Invoke);
		return *this;
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