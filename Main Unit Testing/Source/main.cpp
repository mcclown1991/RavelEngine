#define WIN32_LEAN_AND_MEAN 
#include <Windows.h>
#include <winsock2.h>
#include <RavelEngine.h>
#include <SceneManager.h>
#include "TestScene.h"


int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR, int) {
	RavelEngine::GetRavelEngine()->SystemInit(hInst, true);

	//Initialise all scenes here or have a loading scene to load
	SceneManagement()->AddScene<Scene1>();

	RavelEngine::GetRavelEngine()->SystemRun(std::string());
	RavelEngine::GetRavelEngine()->SystemExit();
}