#include "Sprite2D.h"
#include "RavelEngine.h"
#include "GraphicsManager.h"

Sprite2D::Sprite2D() : Component(){

}

Sprite2D::~Sprite2D(){

}

void Sprite2D::OnStart(){
	
}

void Sprite2D::Update(){
	//m_Sprite->SetScreenPosition(parent->position + transform->position);
}

void Sprite2D::OnDestory(){
	HGE* h = RavelEngine::GetRavelEngine()->GetHGE();
	//delete m_Sprite;
}

void Sprite2D::CreateTexture(std::string texture, float width, float height){

	//HGE* h = RavelEngine::GetRavelEngine()->GetHGE();
	//m_Texture = h->Texture_Load(texture.c_str());
	//m_Texture = GetGFX()->CreateTexture(texture.c_str());
	//m_Sprite = new Sprite(m_Texture, width, height);
	m_Sprite = GetGFX()->CreateTexture(texture, width, height);
	//m_Sprite->SetScreenPosition(parent->position);

	GetGFX()->AddSprite(this);
}

void Sprite2D::Render(){
	(*m_Sprite)->Render(parent->GetPosition() + transform->position);
}