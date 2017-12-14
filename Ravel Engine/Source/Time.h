#ifndef TIME_H
#define TIME_H

#include "RavelEngine.h"

class Time {
public:
	Time();
	~Time();

public:
	float deltaTime;
};

Time* GetTime();

#endif