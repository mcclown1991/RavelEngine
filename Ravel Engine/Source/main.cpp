#include <windows.h>
//#include <stdio.h>
//#include <fcntl.h>
//#include <io.h>
//#include <iostream>
//#include <fstream>
//#include "main.h"
//
////States
//#include "MainMenu.hpp"
//#include "SelectState.hpp"
//
//#include "GraphicsManager.h"
//
//
//const float32	ZOOM			= 1.00f;
//const sInt32	SCREENWIDTH		= (sInt32)(1280.0f * ZOOM);
//const sInt32	SCREENHEIGHT	= (sInt32)(720.0f * ZOOM);
//
//HGE*				hge = 0;
//hgeFont*			fntSmall;
//hgeFont*			fntLarge;
//GameStateManager	gsm;
//
//static const WORD MAX_CONSOLE_LINES = 500;
//
//void showCmd()
//
//{
//	int hConHandle;
//	long lStdHandle;
//
//	CONSOLE_SCREEN_BUFFER_INFO coninfo;
//
//	FILE *fp;
//
//	// allocate a console for this app
//	AllocConsole();
//
//	// set the screen buffer to be big enough to let us scroll text
//	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),&coninfo);
//
//	coninfo.dwSize.Y = MAX_CONSOLE_LINES;
//	SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE),coninfo.dwSize);
//
//	// redirect unbuffered STDOUT to the console
//	lStdHandle = (long)GetStdHandle(STD_OUTPUT_HANDLE);
//	hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);
//	fp = _fdopen( hConHandle, "w" );
//	*stdout = *fp;
//	setvbuf( stdout, NULL, _IONBF, 0 );
//
//	// redirect unbuffered STDIN to the console
//	lStdHandle = (long)GetStdHandle(STD_INPUT_HANDLE);
//	hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);
//	fp = _fdopen( hConHandle, "r" );
//	*stdin = *fp;
//	setvbuf( stdin, NULL, _IONBF, 0 );
//
//	// redirect unbuffered STDERR to the console
//	lStdHandle = (long)GetStdHandle(STD_ERROR_HANDLE);
//	hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);
//	fp = _fdopen( hConHandle, "w" );
//	*stderr = *fp;
//	setvbuf( stderr, NULL, _IONBF, 0 );
//
//	// make cout, wcout, cin, wcin, wcerr, cerr, wclog and clog
//	// point to console as well
//	//ios::sync_with_stdio();
//}
//
//bool Update()
//{
//	// By returning "true" we tell HGE
//	// to stop running the application.
//	if (hge->Input_GetKeyState(HGEK_ESCAPE) ) return true;
//
//	if (!gsm.GSM_Running() )	return true;
//
//	gsm.StateUpdate();
//	// Continue execution
//	return false;
//}
//
//bool MainRender()
//{
//	hge->Gfx_BeginScene();							//start the renderer, frame begins
//	hge->Gfx_Clear(0x00000000);						//ensure scene is cleared
//
//	//gsm.StateDraw();								//call the footyApp render Methods
//	GetGFX()->Render();
//
//	hge->Gfx_EndScene();							//Stop the renderer, frame over
//	return false;
//}
//

//#include "Factory.h"
//#include "Transform.h"
//
//int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) { 
//	factory()->CreateGameObject("test")->AddComponent<Transform>();
//	return 0; }

//
//	//// Enable run-time memory check for debug builds.
//	#if defined(DEBUG) | defined(_DEBUG)
//		_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
//	#endif
//
//#ifdef _DEBUG
//	showCmd();
//#endif
//	// Here we use global posInt32er to HGE sInt32erface.
//	// Instead you may use hgeCreate() every
//	// time you need access to HGE. Just be sure to
//	// have a corresponding hge->Release()
//	// for each call to hgeCreate()
//	hge = hgeCreate(HGE_VERSION);
//
//	hge->System_SetState(HGE_LOGFILE, "GameApp.log");
//
//	// Set our frame function
//	hge->System_SetState(HGE_FRAMEFUNC, Update);
//
//	//hge->System_SetState(HGE_GFXRESTOREFUNC, GfxRestoreFunc);
//
//	// Set our render function
//	hge->System_SetState(HGE_RENDERFUNC, MainRender);
//
//	// Set the window title
//	hge->System_SetState(HGE_TITLE, "Aria Concerto Demo");
//
//	hge->System_SetState(HGE_FPS, 60);
//	
//	// Run in windowed mode
//	// Default window size is 800x600
//	hge->System_SetState(HGE_WINDOWED, true);
//
//	hge->System_SetState(HGE_SCREENWIDTH, (sInt32)SCREENWIDTH);
//	hge->System_SetState(HGE_SCREENHEIGHT,(sInt32)SCREENHEIGHT);
//
//	// Don't use BASS for sound
//	hge->System_SetState(HGE_USESOUND, true);
//
//	hge->System_SetState(HGE_HIDEMOUSE, false);
//
//	// Tries to initiate HGE with the states set.
//	// If something goes wrong, "false" is returned
//	// and more specific description of what have
//	// happened can be read with System_GetErrorMessage().
//	if(hge->System_Initiate())
//	{
//
//		fntLarge=new hgeFont("..\\gfx\\fonts\\font1.fnt");
//		fntSmall=new hgeFont("..\\gfx\\fonts\\font2.fnt");
//
//		GetGlobal()->Initialise(hge,
//								fntLarge,
//								fntSmall,
//								(sInt32)SCREENWIDTH,
//								(sInt32)SCREENHEIGHT, 
//								0.0f, 
//								0.0f);
//
//		GetGlobal()->SetZoomRatio((float32)ZOOM);
//		//touhou.Initialize();
//		
//		
//		gsm.GSM_Init();
//		gsm.GSM_NextState(SelectState::Instance());
//		gsm.ChangeState();
//
//		// Starts running FrameFunc().
//		// Note that the execution "stops" here
//		// until "true" is returned from FrameFunc().
//		hge->System_Start();
//
//		GetGFX()->OnExit();
//		delete fntSmall;
//		delete fntLarge;
//		gsm.GSM_Exit();
//	}
//	else
//	{	
//		// If HGE initialization failed show error message
//		MessageBoxA(NULL, hge->System_GetErrorMessage(), "Error", MB_OK | MB_ICONERROR | MB_APPLMODAL);
//	}
//
//	// Now ESC has been pressed or the user
//	// has closed the window by other means.
//
//	// Restore video mode and free
//	// all allocated resources
//	hge->System_Shutdown();
//
//	// Release the HGE sInt32erface.
//	// If there are no more references,
//	// the HGE object will be deleted.
//	hge->Release();
//
//	return 0;
//}
//
