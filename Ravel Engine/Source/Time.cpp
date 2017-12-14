#include "Time.h"

Time::Time()
{
}

Time::~Time()
{
}

Time* GetTime() {
	static Time s;
	return(&s);
}