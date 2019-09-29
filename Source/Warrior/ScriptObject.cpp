#include "ScriptObject.h"
#include "LuaManager.h"


ScriptObject::ScriptObject()
{
}


const TCHAR * ScriptObject::ToString()
{
	return *(FString::Printf(TEXT("%x[%s]"), this, GetName()));
}

void ScriptObject::RefObject(LuaRef& r)
{
	if (r.IsNull())
		return;
	r.pos = Singleton<LuaManager>::GetInstance()->RefObj(*this, r.GetPtr());
}

void ScriptObject::UnrefObject(LuaRef& r)
{
	if (r.IsNull())
		return;
	Singleton<LuaManager>::GetInstance()->UnrefObj(*this, r.pos);
}

ScriptObject::~ScriptObject()
{
}
