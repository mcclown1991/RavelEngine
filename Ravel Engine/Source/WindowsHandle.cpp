#include <stdio.h>
#include <fcntl.h>
#include <io.h>
#include <iostream>
#include <fstream>

#include "WindowsHandle.h"

WindowsHandle* WINDOW = nullptr;
static const float FRAME_CAP = 60.0f;

void ShowCMD()
{
	AllocConsole();

	HANDLE handle_out = GetStdHandle(STD_OUTPUT_HANDLE);
	int hCrt = _open_osfhandle((long)handle_out, _O_TEXT);
	FILE* hf_out = _fdopen(hCrt, "w");
	setvbuf(hf_out, NULL, _IONBF, 1);
	*stdout = *hf_out;

	HANDLE handle_in = GetStdHandle(STD_INPUT_HANDLE);
	hCrt = _open_osfhandle((long)handle_in, _O_TEXT);
	FILE* hf_in = _fdopen(hCrt, "r");
	setvbuf(hf_in, NULL, _IONBF, 128);
	*stdin = *hf_in;
}

void WindowsHandle::StartFrame()
{
	do
	{
		QueryPerformanceCounter(&time);
	} while ((time.QuadPart - _last) * _freq < 1000000.0f / FRAME_CAP);
}

void WindowsHandle::EndFrame()
{
	++_frames;
	_current = time.QuadPart;// *_freq;

	_fps = (_current - _thisD) *_freq;

	if (_fps >= 1000000.0f)
	{
		gw.fps = _frames * 1000000.0f / _fps;

		_frames = 0;
		_thisD = _current;
	}

	_last = _current;
}

void WindowsHandle::Update(float dt)
{
	UNREFERENCED_PARAMETER(dt);
	// To determine whether any window event is detected
	if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		switch (msg.message)
		{
		case WM_QUIT:
		{
			//QuitGame();
			break;
		}
		}
		//SetMessage(msg);
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}