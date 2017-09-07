#include "Fuzzy_Scene.h"

Fuzzy_Scene Fuzzy_Scene::_Scene;

void Fuzzy_Scene::Init()
{
	GetGraphicsManager()->SetVertexShader("Shaders\\Texture");
	GetGraphicsManager()->SetFragmentShader("Shaders\\Fragments");
	GetGraphicsManager()->LinkProgram();

	Factory::pGOC& m_Test = factory()->CreateGameObject("Test");
	Sprite2D* m_spr = m_Test->AddComponent<Sprite2D>();
	m_spr->CreateTexture("Background.png", 1280, 720);
	m_Test->transform->position = Vector2(10, 0);

	Factory::pGOC& m_Door = factory()->CreateGameObject("Door");
	m_spr = m_Door->AddComponent<Sprite2D>();
	m_spr->CreateTexture("BlueDoor.png", 32, 64);
	m_Door->transform->position = Vector2(500, 0);
	m_Door->transform->Scale(2);
	m_Door->transform->Rotate(45);
}

void Fuzzy_Scene::Load()
{
}

void Fuzzy_Scene::Update()
{
	//Text Updates
}

void Fuzzy_Scene::Free()
{

}

void Fuzzy_Scene::Unload()
{
}

void Fuzzy_Scene::Pause()
{
}

void Fuzzy_Scene::Resume()
{
}

void Fuzzy_Scene::ChangeState(GameStateManager * gsm, uInt32 btnType)
{
}

void Fuzzy_Scene::End(bool hit)
{

}
