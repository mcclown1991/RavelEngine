#pragma once

#include <RavelBehaviour.h>

class CountDown : public RavelBehaviour {
public:
	CountDown() {};
	~CountDown() {};

	void OnStart();
	void Update();

	void Foo();
};