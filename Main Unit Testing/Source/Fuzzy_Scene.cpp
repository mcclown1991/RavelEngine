#include "Fuzzy_Scene.h"

Fuzzy_Scene Fuzzy_Scene::_Scene;

void Fuzzy_Scene::Init()
{
	GetGraphicsManager()->SetVertexShader("Shaders\\Texture.hlsl");
	GetGraphicsManager()->SetFragmentShader("Shaders\\PixelShader.hlsl");

	Factory::pGOC& m_Test = factory()->CreateGameObject("Test");
	Sprite2D* m_spr = m_Test->AddComponent<Sprite2D>();
	m_spr->CreateTexture("Background.png", 1280, 720);
	//m_Test->transform->Scale(100);
	//m_Test->transform->hscale = 1280;
	//m_Test->transform->vscale = 720;
	m_Test->transform->position = Vector2(0, 0);
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
