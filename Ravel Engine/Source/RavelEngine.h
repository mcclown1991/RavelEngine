#ifndef RAVELENGINE_H
#define RAVELENGINE_H

#include <string>
#include <windows.h>
#include <stdio.h>
#include <fcntl.h>
#include <io.h>
#include <iostream>
#include <fstream>

#include "DataType.h"
#include "GameState.h"
#include "Matrix3x3.h"

class RavelEngine{
public:
	void SystemInit(sInt32 Width, sInt32 Height, bool IsWindowed, std::string Title, bool ShowMouse);
	void SystemRun(GameState* State, std::string& errormsg);
	void SystemExit();

	void ResetScene();
	bool IsResetQueried() {
		if (_resetqueued){
			_resetqueued = !_resetqueued;
			return !_resetqueued;
		}
		else
			return _resetqueued;
	}

	static RavelEngine* GetRavelEngine(){ return &m_EngineInstance; }

	HGE* GetHGE() { return hge; }
	GameStateManager* GetStateManager() { return &gsm; }
	hgeFont* GetFontSmall() { return fntSmall; }
	hgeFont* GetFontLarge() { return fntLarge; }

	sInt32 const& GetScreenWidth() const{
		return SCREENWIDTH;
	}
	sInt32 const& GetScreenHeight() const{
		return SCREENHEIGHT;
	}

private:
	RavelEngine();
	~RavelEngine();

	void CommandPrompt();

	static RavelEngine m_EngineInstance;

	HGE*				hge = 0;
	hgeFont*			fntSmall;
	hgeFont*			fntLarge;
	GameStateManager	gsm;

	float32	ZOOM = 1.00f;
	sInt32	SCREENWIDTH;
	sInt32	SCREENHEIGHT;

	bool _resetqueued = false;
};

#endif