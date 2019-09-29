#pragma once
#include "Singleton.h"
#include "LuaManager.h"
#include "LuaAction.h"
#include "LuaClass.h"

class Application : public  ScriptObject, ISingleton
{
public:
	const char* GetName() { return "_""Application"; }
	uint16 GetMeta() { return ClassIndex<Application>::GetIndex(); }
public:
	static void Export();
private:
	LuaAction<double> _onIdle;
	LuaAction<> _onQuit;
	friend Singleton<Application>;
public:
	virtual void OnNew();
	void OnIdle(LuaAction<double> idle);
	void Update(double e);
	void OnQuit(LuaAction<> quit);
	void Quit();
	~Application();
};