#ifndef RAVELTIME_H
#define RAVELTIME_H

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