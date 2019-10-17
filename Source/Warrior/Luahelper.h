#pragma once
#pragma warning(default : 4302)

#include "lua.hpp"
#include "CoreMinimal.h"
#include "Containers/StringConv.h"
#include "ScriptObject.h"
#include "LuaDefine.h"
#include "Logger.h"


template<typename T>
inline T upvalue_(lua_State *L)
{
	return *(T*)lua_touserdata(L, lua_upvalueindex(1));
}

#define ConstructorHead(n, p, m) \
template<p(T,n)>\
struct Constructor m(T, n) {\
	static int Invoke(lua_State* L)\
	{\
		Write(L, new T(
		
		
#define ConstructorTail()\
));\
		return 1;\
	}\
};

#define CONSTRUCTOR(n) ConstructorHead(n, TNNH, VTN) RN(n,0) ConstructorTail()
#define CONSTRUCTORMAX(n) ConstructorHead(n, TNNHD, MVTN) RN(n,0) ConstructorTail()

CONSTRUCTORMAX(10)
CONSTRUCTOR(9)
CONSTRUCTOR(8)
CONSTRUCTOR(7)
CONSTRUCTOR(6)
CONSTRUCTOR(5)
CONSTRUCTOR(4)
CONSTRUCTOR(3)
CONSTRUCTOR(2)
CONSTRUCTOR(1)
CONSTRUCTOR(0)

#define FuncHead( n,p,m ) \
template<typename V, p(T,n)>\
struct Func m(T, n){\
	static int Invoke(lua_State* L)\
	{\
		T* obj = Read<T*>(L, 1);\
		Write(L, (obj->*upvalue_<V(T::*)( TN(n))>(L))(

#define FuncTail() \
));\
		return 1;\
	}\
};

#define FUNC(n) FuncHead(n, TNNH, VTNH) RN(n, 1) FuncTail()
#define FUNCMAX(n) FuncHead(n, TNNHD, MVTNH) RN(n, 1) FuncTail()

FUNCMAX(10)
FUNC(0)
FUNC(1)
FUNC(2)
FUNC(3)
FUNC(4)
FUNC(5)
FUNC(6)
FUNC(7)
FUNC(8)
FUNC(9)

#define FuncVoidHead( n,p ) \
template<p(T,n)>\
struct Func<void, TNH(T,n)> {\
	static int Invoke(lua_State* L)\
	{\
		(Read<T*>(L, 1)->*(upvalue_<void(T::*)(TN(n))>(L)))(

#define FuncVoidTail() \
);\
		return 0;\
	}\
};\

#define VOIDFUNC(n) FuncVoidHead(n, TNNH) RN(n, 1) FuncVoidTail()

template<typename T, typename T1>
struct Func<void, T, T1> {
	typedef void(T::*F)(T1);
	static int Invoke(lua_State* L)
	{
		T* obj = NULL;
		obj = Read<T*>(L, 1);
		F func = upvalue_<F>(L);
		LogWarn("type[%d]",  ClassIndex<T1>::GetIndex());
		T1 a1 = Read<T1>(L, 2);
		(obj->*func)(a1);
		return 0;
	}
};

VOIDFUNC(0)
//VOIDFUNC(1)
VOIDFUNC(2)
VOIDFUNC(3)
VOIDFUNC(4)
VOIDFUNC(5)
VOIDFUNC(6)
VOIDFUNC(7)
VOIDFUNC(8)
VOIDFUNC(9)
VOIDFUNC(10)

#define StaticFuncHead( n,p,m ) \
template<p(V, n)>\
struct StaticFunc m(V,n){\
	static int Invoke(lua_State* L)\
	{\
		Write(L, (*upvalue_<V(*)( TN(n))>(L))(

#define StaticFuncTail() \
));\
		return 1;\
	}\
};

#define STATICFUNC(n) StaticFuncHead(n, TNNH, VTN) RN(n, 0) StaticFuncTail()
#define STATICFUNCMAX(n) StaticFuncHead(n, TNNHD, MVTN) RN(n, 0) StaticFuncTail()

STATICFUNCMAX(10)
STATICFUNC(0)
//FuncHead(0) RN(0) FuncTail()
STATICFUNC(1)
STATICFUNC(2)
STATICFUNC(3)
STATICFUNC(4)
STATICFUNC(5)
STATICFUNC(6)
STATICFUNC(7)
STATICFUNC(8)
STATICFUNC(9)


#define StaticFuncVoidHead( n,p ) \
template<p(n)>\
struct StaticFunc<TNH(void,n)> {\
	static int Invoke(lua_State* L)\
	{\
		(*upvalue_<void(*)(TN(n))>(L))(

#define StaticFuncVoidTail() \
);\
		return 0;\
	}\
};\

#define STATICVOIDFUNC(n) StaticFuncVoidHead(n, TNN) RN(n, 0) StaticFuncVoidTail()

STATICVOIDFUNC(0)
STATICVOIDFUNC(1)
STATICVOIDFUNC(2)
STATICVOIDFUNC(3)
STATICVOIDFUNC(4)
STATICVOIDFUNC(5)
STATICVOIDFUNC(6)
STATICVOIDFUNC(7)
STATICVOIDFUNC(8)
STATICVOIDFUNC(9)
STATICVOIDFUNC(10)

template<typename T1 = void, typename T2 = void, typename T3 = void, typename T4 = void>
struct TypeContainer {
};

template<>
struct TypeContainer<> {
};

template<typename T1>
struct TypeContainer<T1>{
};

template<typename T1, typename T2>
struct TypeContainer<T1,T2> {
};

template<typename T1, typename T2, typename T3>
struct TypeContainer<T1, T2,T3> {
};



template<typename A, typename B, int C = 1> struct go_ { typedef A type; };
template<typename A, typename B> struct go_<A, B, 0> { typedef B type; };

template <typename T>
struct is_enum
{
	static T arg;
	static const bool value = std::is_enum<T>::value ? 1 : 0;
};

template<typename T>
struct is_ptr { static const int value = 0; };
template<typename T>
struct is_ptr<T*> { static const int value = 1; };

template<typename T>
struct is_ref { static const int value = 0; };
template<typename T>
struct is_ref<T&> { static const int value = 1; };

template<typename T>
struct removeptr
{
	typedef T type;
};

template<typename T>
struct removeptr<T*>
{
	typedef T type;
};

template<typename T>
struct removeptr<T&>
{
	typedef T type;
};

template<typename T>
struct lua2ptr {
	static T Invoke(void* p)
	{
		return (T)p;
	}
};

template<typename T>
struct lua2ref {
	static T Invoke(void* p)
	{
		return *(removeptr<T>::type *)p;
	}
};

template<typename T>
 inline T Read(lua_State* L, int i)
{
	 void* p = lua_getuser(L, i);
	 return go_<lua2ptr<T>,lua2ref<T>, is_ptr<T>::value>::type::Invoke(p);
}

 /*template<typename T>
 inline T* Read<T*>(lua_State* L, int i)
 {
	 unimplemented();
 }

 template<typename T>
 inline T& Read(lua_State* L, int i)
 {
	 unimplemented();
 }*/

template<>
 inline int8 Read(lua_State* L, int i)
{
	return (int8)lua_tointeger(L, i);
}

template<>
 inline int16 Read(lua_State* L, int i)
{
	return (int16)lua_tointeger(L, i);
}

template<>
 inline int32 Read(lua_State* L, int i)
{
	return (int32)lua_tointeger(L, i);
}

template<>
 inline uint8 Read(lua_State* L, int i)
{
	return (uint8)lua_tointeger(L, i);
}

template<>
 inline uint16 Read(lua_State* L, int i)
{
	return (uint16)lua_tointeger(L, i);
}

template<>
 inline uint32 Read(lua_State* L, int i)
{
	return (uint32)lua_tointeger(L, i);
}

template<>
 inline uint64 Read(lua_State* L, int i)
{
	return (uint64)lua_tointeger(L, i);
}

template<>
 inline float Read(lua_State* L, int i)
{
	return (float)lua_tonumber(L, i);
}


template<>
 inline double Read(lua_State* L, int i)
{
	return lua_tonumber(L, i);
}

template<>
 inline FString Read(lua_State* L, int i)
{
	uint64 len = 0;
	const char* str = lua_tolstring(L, i, &len);
	return UTF8_TO_TCHAR(str);
}

/*template<>
 inline ScriptObject* Read<ScriptObject*>(lua_State* L, int i)
{
	return (ScriptObject*)lua_getuser(L, i);
}

template<>
 inline ScriptObject& Read<ScriptObject&>(lua_State* L, int i)
{
	return *((ScriptObject*)lua_getuser(L, i));
}*/

template<typename T>
 inline T Pop(lua_State* L, int i)
{
	T t = Read<T>(L, i)
		lua_remove(L, i);
	return t;
}

template<typename T>
 inline void WriteObject(lua_State* L, T i)
{

}

 inline void Write(lua_State* L)
 {
	 lua_pushnil(L);
 }

template<typename T>
 inline void Write(lua_State* L, T i)
{
	 if (is_enum<T>::value)
		 Write(L, (int32)(i));
	 else
		 unimplemented();
}

template<>
 inline void Write(lua_State* L, int8 i)
{
	lua_pushinteger(L, i);
}

template<>
 inline void Write(lua_State* L, int16 i)
{
	lua_pushinteger(L, i);
}

template<>
 inline void Write(lua_State* L, int32 i)
{
	lua_pushinteger(L, i);
}

template<>
 inline void Write(lua_State* L, int64 i)
{
	lua_pushinteger(L, i);
}

template<>
 inline void Write(lua_State* L, uint8 i)
{
	lua_pushinteger(L, i);
}

template<>
 inline void Write(lua_State* L, uint16 i)
{
	lua_pushinteger(L, i);
}

template<>
 inline void Write(lua_State* L, uint32 i)
{
	lua_pushinteger(L, i);
}

template<>
 inline void Write(lua_State* L, uint64 i)
{
	lua_pushinteger(L, i);
}

template<>
 inline void Write(lua_State* L, double d)
{
	lua_pushnumber(L, d);
}

template<>
 inline void Write(lua_State* L, float f)
{
	lua_pushnumber(L, f);
}

template<>
 inline void Write(lua_State*L, const char* s)
{
	lua_pushstring(L, s);
}

template<>
 inline void Write(lua_State*L, FString fs)
{
	const TCHAR* s = fs.GetCharArray().GetData();
	lua_pushstring(L, TCHAR_TO_UTF8(s));
}

 template<>
 inline void Write(lua_State*L, LuaRef f)
 {
	 if (f.IsNull())
		 lua_pushnil(L);
	 else
		 lua_pushhead(L, f.GetPtr());
 }

template<>
 inline void Write(lua_State*L, ScriptObject& o)
{
	void* ptr = o._ptr;
	if (!ptr)
	{
		lua_newtable(L);
		lua_rawgeti(L, LUA_REGISTRYINDEX, o.GetMeta());
		lua_setmetatable(L, -2);
		lua_setuser(L, -1, &o);
		o._ptr = lua_tohead(L, -1);
	}
	else
		lua_pushhead(L, ptr);
}

template<>
 inline void Write(lua_State*L, void* p)
{
	lua_pushlightuserdata(L, p);
}

template<>
inline void Write(lua_State* L, lua_CFunction f)
{
	lua_pushcfunction(L, f);
}

template<typename V, typename T>
 inline void Write(lua_State*L, V(T::*func)())
{
	lua_pushcclosure(L, Func<V, T>::Invoke, 1);
}

template<typename V, typename T, typename T1>
 inline void Write(lua_State*L, V(T::*func)(T1))
{
	lua_pushcclosure(L, Func<V, T, T1>::Invoke, 1);
}

template<typename V, typename T, typename T1, typename T2>
 inline void Write(lua_State*L, V(T::*func)(T1, T2))
{
	lua_pushcclosure(L, Func<V, T, T1, T2>::Invoke, 1);
}

template<typename V>
 inline void Write(lua_State*L, V(*func)())
{
	lua_pushcclosure(L, StaticFunc<V>::Invoke, 1);
}

template<typename V, typename T1>
 inline void Write(lua_State*L, V(*func)(T1))
{
	lua_pushcclosure(L, StaticFunc<V>::Invoke, 1);
}

template<typename V, typename T1, typename T2>
 inline void Write(lua_State*L, V(*func)(T1, T2))
{
	lua_pushcclosure(L, StaticFunc<V, T1, T2>::Invoke, 1);
}


 static int stringfunc(lua_State* L)
 {
	 ScriptObject& obj = Read<ScriptObject&>(L, -1);
	 Write(L, obj.ToString());
	 return 1;
 }

 static int gcfunc(lua_State* L)
 {
	 ScriptObject* obj = Read<ScriptObject*>(L, -1);
	 delete obj;
	 return 0;
 }

 static int newfunc(lua_State* L)
 {
	 int n = lua_gettop(L);
	 if (!lua_getupvalue(L, 1, n))
		 luaL_error(L, "can not New with too many argument[%d]", n);
	 if(lua_isnil(L,-1))
		 luaL_error(L, "can not New with invalid argument number[%d]", n);
	for (int i = 2;i <= n;i++)
		lua_pushvalue(L, i);
	lua_call(L, n - 1, -1);
	return lua_gettop(L) - n;
 }