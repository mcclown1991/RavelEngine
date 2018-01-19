#pragma once

#include <vector>
#include <iterator>
#include <RavelEngine.h>
#include <Time.h>

template <typename T>
using CallBack = void(T::*)();

template <typename T>
class CountDownTimer {
public:
	explicit CountDownTimer(size_t id, double duration, CallBack<T> func, bool repeat = false) : id(id), time(0), elapsed(0), duration(duration) {
		callback = func;
	}
	~CountDownTimer() {}

	size_t GetID() { return id; }
	double GetTimeLeft() { return time; }
	double GetElapsed() { return elapsed; }

	void Update() {
		elapsed += GetTime()->deltaTime;
		time = duration - elapsed;
	}

private:
	size_t id;
	double time, elapsed, duration;
	bool repeat;

	CallBack<T> callback;
};

template <typename T>
class Timer : public RavelBehaviour {
public:
	Timer();
	~Timer();

	virtual void OnStart() {}
	void CreateTimer(double duration, CallBack<T> func, bool repeat = false);
	void Update();

private:
	typename std::vector<CountDownTimer<T>*> m_Timers;
	typename std::vector<CountDownTimer<T>*>::iterator head;
	size_t size, limit;
};