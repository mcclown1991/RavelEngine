#pragma once

#include <Scene.h>

class Scene1 : public Scene {
public:
	Scene1() {};
	virtual void Init();
	virtual void Update();
	virtual void Free();
};