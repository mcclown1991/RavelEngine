#include <windows.h>
#include <RavelEngine.h>

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR, int) {
	RavelEngine::GetRavelEngine()->SystemInit(hInst, true);

	//Initialise all scenes here or have a loading scene to load
	//SceneManagement()->AddScene<Scene1>();

	RavelEngine::GetRavelEngine()->SystemRun(std::string());
	RavelEngine::GetRavelEngine()->SystemExit();
}