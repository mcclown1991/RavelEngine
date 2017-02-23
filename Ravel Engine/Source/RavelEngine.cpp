#include "RavelEngine.h"
#include "Factory.h"
#include "CollisionManager.h"

RavelEngine RavelEngine::m_EngineInstance;

RavelEngine::RavelEngine(){

}

RavelEngine::~RavelEngine(){

}

void RavelEngine::CommandPrompt(){
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

	// make cout, wcout, cin, wcin, wcerr, cerr, wclog and clog
	// point to console as well
	//ios::sync_with_stdio();
}

bool Update()
{
	// By returning "true" we tell HGE
	// to stop running the application.
	if (RavelEngine::GetRavelEngine()->GetHGE()->Input_GetKeyState(HGEK_ESCAPE)) return true;

	if (!RavelEngine::GetRavelEngine()->GetStateManager()->GSM_Running())	return true;

	if (RavelEngine::GetRavelEngine()->IsResetQueried()) {
		factory()->Quit();
		GetGFX()->OnExit();
		RavelEngine::GetRavelEngine()->GetStateManager()->ResetState();

	}

	factory()->Update();
	//GetCollision()->Update();
	RavelEngine::GetRavelEngine()->GetStateManager()->StateUpdate();
	// Continue execution
	return false;
}

bool Render(){
	HGE* hge = RavelEngine::GetRavelEngine()->GetHGE();

	hge->Gfx_BeginScene();							//start the renderer, frame begins
	hge->Gfx_Clear(0x00000000);						//ensure scene is cleared

	GetGFX()->Render();	

	hge->Gfx_EndScene();							//Stop the renderer, frame over
	return false;
}


void RavelEngine::SystemInit(sInt32 Width, sInt32 Height, bool IsWindowed, std::string Title, bool ShowMouse){
	//// Enable run-time memory check for debug builds.
#if defined(DEBUG) | defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

#ifdef _DEBUG
	CommandPrompt();
#endif
	// Here we use global posInt32er to HGE sInt32erface.
	// Instead you may use hgeCreate() every
	// time you need access to HGE. Just be sure to
	// have a corresponding hge->Release()
	// for each call to hgeCreate()
	hge = hgeCreate(HGE_VERSION);

	hge->System_SetState(HGE_LOGFILE, "GameApp.log");

	// Set our frame function
	hge->System_SetState(HGE_FRAMEFUNC, Update);

	//hge->System_SetState(HGE_GFXRESTOREFUNC, GfxRestoreFunc);

	// Set our render function
	hge->System_SetState(HGE_RENDERFUNC, Render);

	// Set the window title
	hge->System_SetState(HGE_TITLE, Title.c_str());

	hge->System_SetState(HGE_FPS, 120);

	// Run in windowed mode
	// Default window size is 800x600
	hge->System_SetState(HGE_WINDOWED, IsWindowed);

	hge->System_SetState(HGE_SCREENWIDTH, (sInt32)Width);
	hge->System_SetState(HGE_SCREENHEIGHT, (sInt32)Height);

	// Don't use BASS for sound
	hge->System_SetState(HGE_USESOUND, true);

	hge->System_SetState(HGE_HIDEMOUSE, !ShowMouse);

	SCREENWIDTH = Width;
	SCREENHEIGHT = Height;
}

void RavelEngine::SystemRun(GameState* State, std::string& errormsg){
	// Tries to initiate HGE with the states set.
	// If something goes wrong, "false" is returned
	// and more specific description of what have
	// happened can be read with System_GetErrorMessage().
	if (hge->System_Initiate())
	{
		//TODO : removed font for now
		fntLarge = new hgeFont("gfx\\font1.fnt");
		fntSmall = new hgeFont("gfx\\font2.fnt");


		gsm.GSM_Init();
		gsm.GSM_NextState(State);
		gsm.ChangeState();

		// Starts running FrameFunc().
		// Note that the execution "stops" here
		// until "true" is returned from FrameFunc().
		hge->System_Start();
		
	}
	else
	{
		// If HGE initialization failed show error message
		//MessageBoxA(NULL, hge->System_GetErrorMessage(), "Error", MB_OK | MB_ICONERROR | MB_APPLMODAL);
		errormsg = hge->System_GetErrorMessage();
	}

	//SystemExit();
}

void RavelEngine::SystemExit(){
	
	delete fntSmall;
	delete fntLarge;
	factory()->Quit();
	gsm.GSM_Exit();
	GetGFX()->OnExit();

	// Now ESC has been pressed or the user
	// has closed the window by other means.

	// Restore video mode and free
	// all allocated resources
	hge->System_Shutdown();

	// Release the HGE sInt32erface.
	// If there are no more references,
	// the HGE object will be deleted.
	hge->Release();
}

void RavelEngine::ResetScene(){
	
	_resetqueued = true;
}