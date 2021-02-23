#include "TestScene.h"
#include <ComponentHeader.h>
#include <AI/BehaviourTree.h>

using namespace std::string_view_literals;

void Scene1::Init()
{
	_path = "";
	_sceneName = "Fuzzy_scene";

	GetGraphicsManager()->SetVertexShader("Shaders\\Texture");
	GetGraphicsManager()->SetFragmentShader("Shaders\\Fragments");
	GetGraphicsManager()->LinkProgram();

	// register all custom components first before loading all prefabs
	factory()->RegisterComponent<Button<Scene1>>("Button<Fuzzy_Scene>");
}

void Scene1::Update()
{
}

void Scene1::Free()
{
	
}
