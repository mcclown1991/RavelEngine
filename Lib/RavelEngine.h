#ifndef RAVELENGINE_H
#define RAVELENGINE_H

#include <string>
#include <windows.h>
#include <stdio.h>
#include <fcntl.h>
#include <io.h>
#include <iostream>
#include <fstream>

#include <rapidjson\document.h>
#include <rapidjson\istreamwrapper.h>

#include "DataType.h"
#include "Matrix3x3.h"
#include "WindowsHandle.h"
#include "DirectX11.h"
#include "OpenGL.h"
#include "Time.h"

#include "Scene.h"
#include "SceneManager.h"

class RavelEngine{
public:
	void SystemInit(HINSTANCE hInstance, int nCmdShow);
	void SystemInit(sInt32 Width, sInt32 Height, bool IsWindowed, std::string Title, bool ShowMouse);
	void SystemRun(std::string& errormsg);
	void SystemExit();
	void QuitRaised();

	HWND GetWindowHandle();

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

	//HGE* GetHGE() { return hge; }
	//GameStateManager* GetStateManager() { return &gsm; }
	//hgeFont* GetFontSmall() { return fntSmall; }
	//hgeFont* GetFontLarge() { return fntLarge; }

	sInt32 const& GetScreenWidth() const{
		return SCREENWIDTH;
	}
	sInt32 const& GetScreenHeight() const{
		return SCREENHEIGHT;
	}

	void SetWindowTitle(std::string const& title);

	Matrix4x4 ScenceTransform() const;

private:
	RavelEngine();
	~RavelEngine();

	bool Update();

	void CommandPrompt();

	static RavelEngine m_EngineInstance;

	//HGE*				hge = 0;
	//hgeFont*			fntSmall;
	//hgeFont*			fntLarge;
	//GameStateManager	gsm;
	WindowsHandle*		pWindow;
	Graphics*			pRenderer;

	float32	ZOOM = 1.00f;
	sInt32	SCREENWIDTH;
	sInt32	SCREENHEIGHT;

	bool _resetqueued = false;
	bool _quit = false;

	Matrix4x4 ref;
};

#endif