#include "BoxCollider.h"
#include "RavelEngine.h"
#include "CollisionManager.h"

BoxCollider::BoxCollider() : hover(nullptr), click(nullptr), release(nullptr)
{
}

BoxCollider::~BoxCollider()
{
}

void BoxCollider::OnStart()
{
}

void BoxCollider::Update()
{
	_Rect->Set(parent->position.x, parent->position.y, parent->position.x + _width, parent->position.y + _height);
	OnMouseOver();
	OnMouseClick();
}

void BoxCollider::OnDestory()
{
	delete _Rect;
}

void BoxCollider::CreateBoxCollider(float width, float height)
{
	_width = width;
	_height = height;
	GetCollision()->AddCollider(this, Vector2(width, height));
	_Rect = new hgeRect(parent->position.x, parent->position.y, parent->position.x + width, parent->position.y + height);
}

void BoxCollider::OnMouseOver()
{
	HGE* hge = RavelEngine::GetRavelEngine()->GetHGE();
	float x, y;
	hge->Input_GetMousePos(&x, &y);
	if (_Rect->TestPoint(x, y)) {
		gameObject->OnMouseHover();
	}
	
}

void BoxCollider::OnMouseClick()
{
	HGE* hge = RavelEngine::GetRavelEngine()->GetHGE();
	float x, y;
	hge->Input_GetMousePos(&x, &y);
	if (_Rect->TestPoint(x, y)) {
		if (hge->Input_KeyDown(HGEK_LBUTTON))
			gameObject->OnMouseDown();
	}
}

void BoxCollider::OnMouseRelease()
{
}

void BoxCollider::OnCollision(BoxCollider * other)
{
	gameObject->OnCollisionEnter(other);
}
