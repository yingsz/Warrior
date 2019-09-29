#include "Application.h"

template<>
Application* Singleton<Application>::_instance = NULL;

void Application::OnNew()
{
	_onIdle = 0;
}

void Application::OnIdle(LuaAction<double> idle)
{
	SAFE_ASSIGN(_onIdle,idle);
}

void Application::Update(double e)
{
	if (!_onIdle.IsNull())
		_onIdle(e);
}

void Application::OnQuit(LuaAction<> quit)
{
	SAFE_ASSIGN(_onQuit, quit);
}

void Application::Export()
{
	_SCRIPT_DEF_BEGIN(Application)
		_SCRIPT_DEF_FUNC(OnIdle)
		_SCRIPT_DEF_FINISH()
}

void Application::Quit()
{
	if (!_onQuit.IsNull())
		_onQuit();
}

Application::~Application()
{
}
