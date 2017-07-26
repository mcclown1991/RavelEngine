#include <Windows.h>
#include <RavelEngine.h>
#include "Fuzzy_Scene.h"

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR, int) {
	RavelEngine::GetRavelEngine()->SystemInit(hInst, true);
	RavelEngine::GetRavelEngine()->SystemRun(Fuzzy_Scene::Instance(), std::string());
	RavelEngine::GetRavelEngine()->SystemExit();
}