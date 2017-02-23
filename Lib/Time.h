#ifndef TIME_H
#define TIME_H

#include "Component.h"
#include "RavelEngine.h"

class Time : public Component {
public:
	Time();
	virtual ~Time();

	virtual void OnStart();
	virtual void Update();
	virtual void OnDestory();

	float GetTimeElapsed();
	void StartTimer();
	void PauseTimer();
	float QueryTimer();
	float StopTimer();

private:
	HGE* hge;
	float _dt;
	bool _timertick;
};

#endif