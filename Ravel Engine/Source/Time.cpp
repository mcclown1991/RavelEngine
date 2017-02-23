#include "Time.h"

Time::Time() : hge(nullptr), _dt(0.f), _timertick(false)
{
}

Time::~Time()
{
}

void Time::OnStart()
{
	hge = RavelEngine::GetRavelEngine()->GetHGE();
}

void Time::Update()
{
	if (_timertick)
		_dt += hge->Timer_GetDelta();
}

void Time::OnDestory()
{
}

float Time::GetTimeElapsed()
{
	return hge->Timer_GetTime();
}

void Time::StartTimer()
{
	_timertick = true;
}

void Time::PauseTimer()
{
	_timertick = !_timertick;
}

float Time::QueryTimer()
{
	return _dt;
}

float Time::StopTimer()
{
	_timertick = false;
	float dt = _dt;
	_dt = 0.f;
	return dt;
}
