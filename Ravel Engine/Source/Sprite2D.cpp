#include "Sprite2D.h"
#include "RavelEngine.h"
#include "GraphicsManager.h"

Sprite2D::Sprite2D() : RavelBehaviour(){

}

Sprite2D::~Sprite2D(){

}

void Sprite2D::OnStart(){

}

void Sprite2D::Update(){
	//m_Sprite->SetScreenPosition(parent->position + transform->position);
}

void Sprite2D::OnDestory(){
	//HGE* h = RavelEngine::GetRavelEngine()->GetHGE();
	//delete m_Sprite;
	m_Model->OnDestory();
	delete m_Model;
}

void Sprite2D::CreateTexture(std::string texture, float width, float height){
	GetGraphicsManager()->Renderer()->CreateTexture(texture, m_SampleID);
	m_Model = new Transform();
	m_Model->hscale = width * 0.89f;
	m_Model->vscale = height * 0.89f;
	m_UV = Vector2(0.f, 0.f);
	m_Size = Vector2(1, 1);

	m_Dimension = Vector2(width, height);

	GetGraphicsManager()->AddSprite(this);
}

void Sprite2D::Render(){

	//Find Position, Rotation and Scale then transform
	//assume a reference frome from center of this sprite first

	Vector2 view = parent->GetPosition() + transform->position;

	Matrix4x4 trans = transform->GetTransforms() * m_Model->GetLocalTransforms();
	//trans = m_Reference_Frame * trans;
	//Vector2 vertice[4];

	/*vertice[0] = trans * m_Vertex[0];
	vertice[1] = trans * m_Vertex[1];
	vertice[2] = trans * m_Vertex[2];
	vertice[3] = trans * m_Vertex[3];*/

	GetGraphicsManager()->Renderer()->Render(m_SampleID, trans, m_UV, m_Size, true, 1);

	//vertice[0] = m_Reference_Frame * vertice[0];
	//vertice[1] = m_Reference_Frame * vertice[1];
	//vertice[2] = m_Reference_Frame * vertice[2];
	//vertice[3] = m_Reference_Frame * vertice[3];

	//(*m_Sprite)->Render(view, parent->localEulerAngles + transform->localEulerAngles, transform->hscale, transform->vscale);

	//(*m_Sprite)->Render(vertice);
}