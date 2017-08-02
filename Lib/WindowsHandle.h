#ifndef WINDOWSHANDLE_H
#define WINDOWSHANDLE_H

#include <windows.h>
#include <windowsx.h>
#include <string>

#include "System.h"

class WindowsHandle : public System {
private:
	struct GAMEWINDOW
	{
		HWND hWnd;
		HINSTANCE hInst;
		int Width, Height;
		bool Windowed;
		float fps;

		GAMEWINDOW() : hWnd(nullptr), hInst(nullptr), Width(0), Height(0), Windowed(true), fps(1000.0f)
		{
		}
	};

	enum RENDERER { DIRECTX11, OPENGL };

	struct USERPREF
	{
		bool fullscreen_;
		unsigned int renderer_;
		bool xbox_;
	};

	USERPREF user;
	LONGLONG _frames, _current, _last, _thisD;
	float _fps;
	float _freq;

	// Create a message
	MSG msg;
	MSG defltultMsg;
	PBYTE key;
	GAMEWINDOW gw;

	LARGE_INTEGER time;
	LARGE_INTEGER freq;

	bool isFullScreen;

public:
	WindowsHandle() : System() {	}

	void Init() {}

	bool InitConfigure(HINSTANCE hInstance, int nCmdShow);
	bool InitWindow(HINSTANCE hInstance, int nCmdShow);
	bool InitWindow(HWND hWnd, int nCmdShow);

	float getLastFrameTime();
	float getFPS();
	void SetWindowTitle(char* title);

	void InitWindowHandle(HINSTANCE hInstance, int nCmdShow, bool console = false);
	void InitWindowHandle(HWND hWnd, int nCmdShow, bool console = false);

	void Update();

	GAMEWINDOW* getWindowHandle();
	USERPREF* getUSER();

	void StartFrame();
	void EndFrame();
};

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

#endif