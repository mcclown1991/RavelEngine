#include "RavelEngine.h"
#include "Factory.h"
#include "CollisionManager.h"
#include "Font.h"

RavelEngine RavelEngine::m_EngineInstance;

RavelEngine::RavelEngine(){
	pWindow = new WindowsHandle();
}

RavelEngine::~RavelEngine(){

}

HWND RavelEngine::GetWindowHandle() {
	return pWindow->getWindowHandle()->hWnd;
}

void RavelEngine::CommandPrompt(){

	FILE *fp;

	// allocate a console for this app
	AllocConsole();

	freopen_s(&fp, "CONOUT$", "w", stdout);

}


void RavelEngine::SystemInit(HINSTANCE hInstance, int nCmdShow) {
	//// Enable run-time memory check for debug builds.
#if defined(DEBUG) | defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

#ifdef _DEBUG
	CommandPrompt();

	std::cout << "=============================================================\n";
	std::cout << "	Initialising Ravel Engine\n";
	std::cout << "=============================================================" << std::endl;
	std::cout << "Setting up Window settings.........." << std::endl;
	pWindow->InitWindowHandle(hInstance, nCmdShow, true);
	std::cout << "Done!" << std::endl;
	std::cout << "=============================================================" << std::endl;
	std::cout << "Setting up Rendering Engine.........." << std::endl;
#else
	pWindow->InitWindowHandle(hInstance, nCmdShow, false);
#endif
	
	
	switch (pWindow->getUSER()->renderer_) {
	case 0:
		pRenderer = new DirectX11();
		break;
	case 1:
		pRenderer = new OpenGL();
		break;
	}

	
	SCREENHEIGHT = pWindow->getWindowHandle()->Height;
	SCREENWIDTH = pWindow->getWindowHandle()->Width;
	pRenderer->Initialise(pWindow->getWindowHandle()->hWnd, pWindow->getWindowHandle()->Width, pWindow->getWindowHandle()->Height, pWindow->getWindowHandle()->Windowed);
	GetGraphicsManager()->InitialiseGraphicsManager(pRenderer);

	ref.m[3] = (float)(-SCREENWIDTH >> 1);
	ref.m[7] = (float)(-SCREENHEIGHT >> 1);
#ifdef _DEBUG
	std::cout << "Done!" << std::endl;
	std::cout << "=============================================================" << std::endl;
	std::cout << "Setting up Collision Manager settings.........." << std::endl;
#endif
	GetCollision()->InitCollisionMangaer();
#ifdef _DEBUG
	std::cout << "Done!" << std::endl;
	std::cout << "=============================================================" << std::endl;
	std::cout << "Setting up Memory settings.........." << std::endl;
#endif
	Memory()->AllocateBlock(107374182);
#ifdef _DEBUG
	std::cout << "Done!" << std::endl;
	std::cout << "=============================================================" << std::endl;
	std::cout << "Setting up Component Factory settings.........." << std::endl;
#endif
	factory()->Init();
#ifdef _DEBUG
	std::cout << "Done!" << std::endl;
	std::cout << "=============================================================" << std::endl;
	std::cout << "Setting up Font Engine settings.........." << std::endl;
#endif
	GetFontManager()->Init();
	GetFontManager()->AddFont("font1", "font1");
#ifdef _DEBUG
	std::cout << "Done!" << std::endl;
	std::cout << "=============================================================" << std::endl;
	std::cout << "Loading Scene Data.........." << std::endl;
#endif
	SceneManagement()->Init();

#ifdef _DEBUG
	std::cout << "Done!" << std::endl;
	std::cout << "=============================================================" << std::endl;
#endif
}

void RavelEngine::SetWindowTitle(std::string const& title) {
	pWindow->SetWindowTitle(const_cast<char*>(title.c_str()));
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
	//hge = hgeCreate(HGE_VERSION);

	//hge->System_SetState(HGE_LOGFILE, "GameApp.log");

	//// Set our frame function
	//hge->System_SetState(HGE_FRAMEFUNC, ::Update);

	////hge->System_SetState(HGE_GFXRESTOREFUNC, GfxRestoreFunc);

	//// Set our render function
	//hge->System_SetState(HGE_RENDERFUNC, Render);

	//// Set the window title
	//hge->System_SetState(HGE_TITLE, Title.c_str());

	//hge->System_SetState(HGE_FPS, 120);

	//// Run in windowed mode
	//// Default window size is 800x600
	//hge->System_SetState(HGE_WINDOWED, IsWindowed);

	//hge->System_SetState(HGE_SCREENWIDTH, (sInt32)Width);
	//hge->System_SetState(HGE_SCREENHEIGHT, (sInt32)Height);

	//// Don't use BASS for sound
	//hge->System_SetState(HGE_USESOUND, true);

	//hge->System_SetState(HGE_HIDEMOUSE, !ShowMouse);

	SCREENWIDTH = Width;
	SCREENHEIGHT = Height;
	
}

bool RavelEngine::Update() {
	float dt = pWindow->getLastFrameTime();

	pWindow->StartFrame();

	if (pWindow->getFPS() <= 60.f && pWindow->getFPS() > 1.f) {
		pWindow->Update();

		if (IsResetQueried()) {
			factory()->Quit();
			GetGraphicsManager()->OnExit();
			//RavelEngine::GetRavelEngine()->GetStateManager()->ResetState();
		}

		factory()->Update();
		GetCollision()->Update();
		//GetStateManager()->StateUpdate();
		GetGraphicsManager()->Render();
		GetTime()->deltaTime = dt;
	}

	pWindow->EndFrame();
	return true;
}

void RavelEngine::SystemRun(std::string& errormsg){
	// Tries to initiate HGE with the states set.
	// If something goes wrong, "false" is returned
	// and more specific description of what have
	// happened can be read with System_GetErrorMessage().

	//if (hge->System_Initiate())
	//{
	//	//TODO : removed font for now
	//	fntLarge = new hgeFont("gfx\\font1.fnt");
	//	fntSmall = new hgeFont("gfx\\font2.fnt");


	//	gsm.GSM_Init();
	//	gsm.GSM_NextState(State);
	//	gsm.ChangeState();

	//	// Starts running FrameFunc().
	//	// Note that the execution "stops" here
	//	// until "true" is returned from FrameFunc().
	//	hge->System_Start();
	//	
	//}
	//else
	//{
	//	// If HGE initialization failed show error message
	//	//MessageBoxA(NULL, hge->System_GetErrorMessage(), "Error", MB_OK | MB_ICONERROR | MB_APPLMODAL);
	//	errormsg = hge->System_GetErrorMessage();
	//}

	//SystemExit();

	/*gsm.GSM_Init();
	gsm.GSM_NextState(State);
	gsm.ChangeState();*/
	SceneManagement()->LoadScene(0);

	while (!_quit) {
		Update();
	}
}

void RavelEngine::SystemExit(){
	
	//delete fntSmall;
	//delete fntLarge;
	GetCollision()->OnExit();
	
	//gsm.GSM_Exit();
	GetGraphicsManager()->OnExit();

	pRenderer->UnInitialise();
	factory()->Quit();

	delete pWindow;
	delete pRenderer;
	// Now ESC has been pressed or the user
	// has closed the window by other means.

	// Restore video mode and free
	// all allocated resources
	//hge->System_Shutdown();

	// Release the HGE sInt32erface.
	// If there are no more references,
	// the HGE object will be deleted.
	//hge->Release();
}

void RavelEngine::QuitRaised() {
	_quit = true;
}

void RavelEngine::ResetScene(){
	
	_resetqueued = true;
}

Matrix4x4 RavelEngine::ScenceTransform() const {
	return ref;
}