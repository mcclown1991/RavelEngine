#ifndef RAVELENGINE_H
#define RAVELENGINE_H

#include <string>
#include <string_view>
#include <windows.h>
#include <stdio.h>
#include <fcntl.h>
#include <io.h>
#include <iostream>
#include <fstream>

#include <rapidjson\document.h>
#include <rapidjson\istreamwrapper.h>
#include <rapidjson\ostreamwrapper.h>
#include <rapidjson\prettywriter.h>
#include <rapidjson\writer.h>
#include <rapidjson\stringbuffer.h>

#include "DataType.h"
#include "Matrix3x3.h"
#include "WindowsHandle.h"
#include "DirectX11.h"
#include "OpenGL.h"
#include "RavelTime.h"

using namespace std::string_view_literals;

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

	sInt32 const& GetScreenWidth() const{
		return SCREENWIDTH;
	}
	sInt32 const& GetScreenHeight() const{
		return SCREENHEIGHT;
	}

	void SetWindowTitle(std::string const& title);

	Matrix4x4 ScenceTransform() const;

	static constexpr std::string_view getGameDataPath() noexcept {
		return GAMEDATA_PATH;
	}

private:
	RavelEngine();
	~RavelEngine();

	bool Update();

	void CommandPrompt();

	static RavelEngine m_EngineInstance;

	WindowsHandle*		pWindow;
	Graphics*			pRenderer;

	float32	ZOOM = 1.00f;
	sInt32	SCREENWIDTH;
	sInt32	SCREENHEIGHT;

	bool _resetqueued = false;
	bool _quit = false;

	Matrix4x4 ref;

	static constexpr std::string_view GAMEDATA_PATH = "GameData\\"sv;
};

#endif