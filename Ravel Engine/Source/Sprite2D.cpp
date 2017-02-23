#include "Sprite2D.h"
#include "RavelEngine.h"
#include "GraphicsManager.h"

Sprite2D::Sprite2D() : Component(){

}

Sprite2D::~Sprite2D(){

}

void Sprite2D::OnStart(){
	m_Vertex[0] = Vector2();
	m_Vertex[1] = Vector2();
	m_Vertex[2] = Vector2();
	m_Vertex[3] = Vector2();
}

void Sprite2D::Update(){
	//m_Sprite->SetScreenPosition(parent->position + transform->position);
}

void Sprite2D::OnDestory(){
	HGE* h = RavelEngine::GetRavelEngine()->GetHGE();
	//delete m_Sprite;
}

void Sprite2D::CreateTexture(std::string texture, float width, float height){

	m_Sprite = GetGFX()->CreateTexture(texture, width, height);

	m_Vertex[1].x += width;
	m_Vertex[2].x += width;
	m_Vertex[2].y += height;
	m_Vertex[3].y += height;

	Vector2 x = m_Vertex[1] - m_Vertex[0];
	Vector2 y = m_Vertex[3] - m_Vertex[0];
	x.Normalize();
	y.Normalize();

	m_Reference_Frame.m[0] = 1;
	m_Reference_Frame.m[1] = 0;
	m_Reference_Frame.m[2] = -width / 2;
	m_Reference_Frame.m[3] = 0;
	m_Reference_Frame.m[4] = 1;
	m_Reference_Frame.m[5] = -height / 2;

	for (Vector2& vertex : m_Vertex) {
		vertex = m_Reference_Frame * vertex;
	}

	m_Reference_Frame.m[2] = -width;
	m_Reference_Frame.m[5] = -height;

	GetGFX()->AddSprite(this);
}

void Sprite2D::Render(){

	//Find Position, Rotation and Scale then transform
	//assume a reference frome from center of this sprite first

	Vector2 view = parent->GetPosition() + transform->position;

	Matrix3x3 trans = transform->GetTransforms();
	//trans = m_Reference_Frame * trans;
	Vector2 vertice[4];

	vertice[0] = trans * m_Vertex[0];
	vertice[1] = trans * m_Vertex[1];
	vertice[2] = trans * m_Vertex[2];
	vertice[3] = trans * m_Vertex[3];

	//vertice[0] = m_Reference_Frame * vertice[0];
	//vertice[1] = m_Reference_Frame * vertice[1];
	//vertice[2] = m_Reference_Frame * vertice[2];
	//vertice[3] = m_Reference_Frame * vertice[3];

	//(*m_Sprite)->Render(view, parent->localEulerAngles + transform->localEulerAngles, transform->hscale, transform->vscale);

	(*m_Sprite)->Render(vertice);
}