#include <stdio.h>
#include <fcntl.h>
#include <io.h>
#include <iostream>
#include <fstream>

#include "WindowsHandle.h"
#include "Input.h"

WindowsHandle* WINDOW = nullptr;
static const float FRAME_CAP = 60.0f;

void ShowCMD()
{
	int hConHandle;
	long lStdHandle;

	CONSOLE_SCREEN_BUFFER_INFO coninfo;

	FILE *fp;

	// allocate a console for this app
	AllocConsole();

	// set the screen buffer to be big enough to let us scroll text
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &coninfo);

	coninfo.dwSize.Y = 500;
	SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), coninfo.dwSize);

	// redirect unbuffered STDOUT to the console
	lStdHandle = (long)GetStdHandle(STD_OUTPUT_HANDLE);
	hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);
	fp = _fdopen(hConHandle, "w");
	*stdout = *fp;
	setvbuf(stdout, NULL, _IONBF, 0);

	// redirect unbuffered STDIN to the console
	lStdHandle = (long)GetStdHandle(STD_INPUT_HANDLE);
	hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);
	fp = _fdopen(hConHandle, "r");
	*stdin = *fp;
	setvbuf(stdin, NULL, _IONBF, 0);

	// redirect unbuffered STDERR to the console
	lStdHandle = (long)GetStdHandle(STD_ERROR_HANDLE);
	hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);
	fp = _fdopen(hConHandle, "w");
	*stderr = *fp;
	setvbuf(stderr, NULL, _IONBF, 0);
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

void WindowsHandle::Update()
{
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
		SetMessage(msg);
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}


// Process the Messages
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
	{
		PostQuitMessage(0);

		return 0;
	} break;
	case WM_ACTIVATEAPP:
	{
		break;
	}
	case WM_ACTIVATE:
	{
		//std::cout << "Focus : " << isFocus << std::endl;
		//if (wParam == WA_INACTIVE)
		//{
		//	isPause = IsGamePaused();

		//	RavelEngine()->PauseGame(true);
		//	if (isFocus && DirectX11::FullScreen()) {
		//		std::cout << "Losing Focus" << std::endl;
		//		DirectX11::LoseFocus();
		//		wasFull = true;
		//		ShowWindow(WINDOW->getWindowHandle()->hWnd, SW_MINIMIZE);

		//	}
		//	isFocus = false;
		//}
		//else
		//{
		//	if (!isPause)
		//		RavelEngine()->PauseGame(false);

		//	if (!isFocus && wasFull)
		//	{
		//		if (D3D)
		//			DirectX11::SwitchFullScreen();
		//		//ShowWindow(WINDOW->getWindowHandle()->hWnd, SW_RESTORE);
		//		wasFull = false;

		//	}
		//	isFocus = true;
		//}
		break;
	} break;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}


bool WindowsHandle::InitWindow(HINSTANCE hInstance, int nCmdShow)
{
	WNDCLASSEX wc;

	ZeroMemory(&wc, sizeof(WNDCLASSEX));
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.lpfnWndProc = (WNDPROC)WindowProc;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.lpszClassName = TEXT("WindowClass");

	RegisterClassEx(&wc);

	ShowCursor(false);

	RECT desktopRect;

	GetWindowRect(GetDesktopWindow(), &desktopRect);

	gw.hWnd = CreateWindowEx(NULL,
		wc.lpszClassName,
		TEXT("Ravel Engine"),
		gw.Windowed ? WS_SYSMENU : WS_EX_TOPMOST | WS_POPUP,
		(desktopRect.right - gw.Width) >> 1, (desktopRect.bottom - gw.Height) >> 1,
		gw.Width, gw.Height,
		NULL,
		NULL,
		hInstance,
		NULL);

	ShowWindow(gw.hWnd, nCmdShow);

	gw.hInst = hInstance;

	_frames = 0;
	_current = 0;

	QueryPerformanceFrequency(&freq);
	_freq = 1000000.0f / freq.QuadPart;

	_last = 0;
	_thisD = 0;

	return true;
}

bool WindowsHandle::InitWindow(HWND hWnd, int nCmdShow)
{
	UNREFERENCED_PARAMETER(nCmdShow);
	gw.hWnd = hWnd;

	gw.hInst = reinterpret_cast<HINSTANCE>(GetWindowLong(hWnd, GWL_HINSTANCE));

	_frames = 0;
	_current = 0;
	LARGE_INTEGER time;
	QueryPerformanceCounter(&time);
	_last = time.QuadPart;
	_thisD = time.QuadPart;

	QueryPerformanceFrequency(&freq);
	_freq = 1000000.0f / freq.QuadPart;

	return true;
}

bool WindowsHandle::InitConfigure(HINSTANCE hInstance, int nCmdShow)
{
	std::ifstream myReadFile;
	myReadFile.open("config.cfg");

	std::string temp;

	if (myReadFile.is_open()) {
		std::getline(myReadFile, temp); // Saves the line in STRING
		std::string::iterator iter;
		iter = temp.begin();
		for (char t : temp)
		{
			iter++;
			if (t == '=')
			{
				temp.erase(temp.begin(), iter);
				break;
			}
		}
		if (temp.compare(" true") == 0)
		{
			user.fullscreen_ = true;
			std::cout << "Fullscreen = True" << std::endl;
		}
		else
		{
			user.fullscreen_ = false;
			std::cout << "Fullscreen = False" << std::endl;
		}
		temp.empty();
		gw.Windowed = !user.fullscreen_;
		std::getline(myReadFile, temp);
		{
			iter = temp.begin();
			for (char t : temp)
			{
				iter++;
				if (t == '=')
				{
					temp.erase(temp.begin(), iter);
					break;
				}
			}
		}
		if (temp.compare(" DirectX 11") == 0)
		{
			user.renderer_ = DIRECTX11;
			std::cout << "Renderer = DirectX 11" << std::endl;
		}
		else
		{
			//user.renderer_ = DIRECTX9;
			user.renderer_ = OPENGL;
			std::cout << "Renderer = OpenGL" << std::endl;
		}

		temp.empty();

		std::getline(myReadFile, temp);
		{
			iter = temp.begin();
			for (char t : temp)
			{
				iter++;
				if (t == '=')
				{
					temp.erase(temp.begin(), iter);
					break;
				}
			}
		}
		if (temp.compare(" YES") == 0)
		{
			user.xbox_ = true;
			std::cout << "XBox Controller = True" << std::endl;
		}
		else
		{
			user.xbox_ = false;
			std::cout << "XBox Controller = False" << std::endl;
		}

		std::getline(myReadFile, temp);
		{
			iter = temp.begin();
			for (char t : temp)
			{
				iter++;
				if (t == '=')
				{
					temp.erase(temp.begin(), iter);
					break;
				}
			}
		}
		if (temp.compare(" 1920 x 1080 @ 60Hz") == 0)
		{
			gw.Width = 1980;
			gw.Height = 1080;
			std::cout << "Resolution = " << temp << std::endl;
		}
		else if (temp.compare(" 1600 x 1024 @ 60Hz") == 0)
		{
			gw.Width = 1600;
			gw.Height = 1024;
			std::cout << "Resolution = " << temp << std::endl;
		}
		else if (temp.compare(" 1600 x 900 @ 60Hz") == 0)
		{
			gw.Width = 1600;
			gw.Height = 900;
			std::cout << "Resolution = " << temp << std::endl;
		}
		else if (temp.compare(" 1440 x 1080 @ 60Hz") == 0)
		{
			gw.Width = 1440;
			gw.Height = 1080;
			std::cout << "Resolution = " << temp << std::endl;
		}
		else if (temp.compare(" 1440 x 960 @ 60Hz") == 0)
		{
			gw.Width = 1440;
			gw.Height = 960;
			std::cout << "Resolution = " << temp << std::endl;
		}
		else if (temp.compare(" 1280 x 1024 @ 60Hz") == 0)
		{
			gw.Width = 1280;
			gw.Height = 1024;
			std::cout << "Resolution = " << temp << std::endl;
		}
		else if (temp.compare(" 1366 x 768 @ 60Hz") == 0)
		{
			gw.Width = 1366;
			gw.Height = 768;
			std::cout << "Resolution = " << temp << std::endl;
		}
		else if (temp.compare(" 1280 x 800 @ 60Hz") == 0)
		{
			gw.Width = 1280;
			gw.Height = 800;
			std::cout << "Resolution = " << temp << std::endl;
		}
		else if (temp.compare(" 1280 x 720 @ 60Hz") == 0)
		{
			gw.Width = 1280;
			gw.Height = 720;
			std::cout << "Resolution = " << temp << std::endl;
		}
		else if (temp.compare(" 1024 x 768 @ 60Hz") == 0)
		{
			gw.Width = 1024;
			gw.Height = 768;
			std::cout << "Resolution = " << temp << std::endl;
		}
		else if (temp.compare(" 800 x 600 @ 60Hz") == 0)
		{
			gw.Width = 800;
			gw.Height = 600;
			std::cout << "Resolution = " << temp << std::endl;
		}
	}
	else
	{
		PROCESS_INFORMATION ProcessInfo; //This is what we get as an [out] parameter

		STARTUPINFO StartupInfo; //This is an [in] parameter

		ZeroMemory(&ProcessInfo, sizeof(ProcessInfo));

		ZeroMemory(&StartupInfo, sizeof(StartupInfo));
		StartupInfo.cb = sizeof StartupInfo; //Only compulsory field

		if (!CreateProcess(L"./Configuration.exe",
			0,
			0,
			0,
			NULL,
			0,
			NULL,
			NULL,
			&StartupInfo,
			&ProcessInfo)) {
			MessageBox(gw.hWnd, L"Error Launching configurations!", L"Error", 0);
		}

		WaitForSingleObject(ProcessInfo.hProcess, INFINITE);
		CloseHandle(ProcessInfo.hThread);
		CloseHandle(ProcessInfo.hProcess);

		InitConfigure(hInstance, nCmdShow);
	}
	myReadFile.close();

	return 0;
}

WindowsHandle::GAMEWINDOW* WindowsHandle::getWindowHandle()
{
	return &gw;
}

WindowsHandle::USERPREF* WindowsHandle::getUSER()
{
	return &user;
}

float WindowsHandle::getLastFrameTime()
{
	return 1.0f / gw.fps;
}

float WindowsHandle::getFPS()
{
	return gw.fps;
}

void WindowsHandle::SetWindowTitle(char* title)
{
	wchar_t wString[4096];
	MultiByteToWideChar(CP_ACP, 0, title, -1, wString, 4096);
	SetWindowText(gw.hWnd, wString);
}

void WindowsHandle::InitWindowHandle(HINSTANCE hInstance, int nCmdShow, bool console)
{
	//D3D = wasFull = false;

	if (console)
		ShowCMD();

	InitConfigure(hInstance, nCmdShow);

	InitWindow(hInstance, nCmdShow);

	//if (user.renderer_ == DIRECTX11)
	//
		//DirectX11::InitDirect3D(gw.hWnd, gw.Windowed, gw.Width, gw.Height);
	//}
	//else if (user.renderer_ == OPENGL)
		//DirectX9::InitDirect3D(gw.hWnd, gw.Windowed, gw.Width, gw.Height);

	////InitXAudio();
	InitInput(gw.hWnd);
	//D3D = true;
}

void WindowsHandle::InitWindowHandle(HWND hWnd, int nCmdShow, bool console)
{
	if (console)
		ShowCMD();

	InitConfigure(reinterpret_cast<HINSTANCE>(GetWindowLong(hWnd, GWL_HINSTANCE)), nCmdShow);

	InitWindow(hWnd, nCmdShow);

	//if (user.renderer_ == DIRECTX11)
	//{
	//	DirectX11::InitDirect3D(gw.hWnd, gw.Windowed, gw.Width, gw.Height);
	//}
	//else if (user.renderer_ == DIRECTX9)
	//	DirectX9::InitDirect3D(gw.hWnd, gw.Windowed, gw.Width, gw.Height);

	////InitXAudio();
	//InitInput(gw.hWnd);
}