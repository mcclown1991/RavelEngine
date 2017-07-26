#ifndef FUZZY_SCENE_H
#define FUZZY_SCENE_H

#include "GameState.h"
#include "main.h"
#include "GameObject.h"
#include "Factory.h"
#include "RavelEngine.h"

class Fuzzy_Scene : public GameState {
public:

	void Init();
	void Load();

	void Update();
	//void Draw();

	void Free();
	void Unload();

	void Pause();
	void Resume();

	void ChangeState(GameStateManager *gsm, uInt32 btnType);
	static Fuzzy_Scene *Instance() { return &_Scene; }

	void End(bool hit);

private:
	static Fuzzy_Scene _Scene;	//!< static instance of state

};

#endif
