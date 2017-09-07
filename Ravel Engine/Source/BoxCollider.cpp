#include "BoxCollider.h"
#include "RavelEngine.h"
#include "CollisionManager.h"

BoxCollider::BoxCollider() : hover(nullptr), click(nullptr), release(nullptr)
{
	std::cout << "Creating new Box Collider" << std::endl;

	//create new rect
	//_rect = new RavelRect()
}

BoxCollider::~BoxCollider()
{
}

void BoxCollider::OnStart()
{
}

void BoxCollider::Update()
{
	OnMouseOver();
	OnMouseClick();
}

void BoxCollider::OnDestory()
{
	//delete _Rect;
}

void BoxCollider::CreateBoxCollider() {
	_width = gameObject->transform->hscale * 2;
	_height = gameObject->transform->vscale * 2;
	GetCollision()->AddCollider(this, Vector2(_width, _height));
}

void BoxCollider::CreateBoxCollider(float width, float height)
{
	_width = width;
	_height = height;
	GetCollision()->AddCollider(this, Vector2(width, height));
	//_Rect = new hgeRect(parent->position.x, parent->position.y, parent->position.x + width, parent->position.y + height);
}

void BoxCollider::OnMouseOver()
{
	//HGE* hge = RavelEngine::GetRavelEngine()->GetHGE();
	//float x, y;
	/*hge->Input_GetMousePos(&x, &y);
	if (_Rect->TestPoint(x, y)) {
		gameObject->OnMouseHover();
	}*/
	
}

void BoxCollider::OnMouseClick()
{
	/*HGE* hge = RavelEngine::GetRavelEngine()->GetHGE();
	float x, y;
	hge->Input_GetMousePos(&x, &y);
	if (_Rect->TestPoint(x, y)) {
		if (hge->Input_KeyDown(HGEK_LBUTTON))
			gameObject->OnMouseDown();
	}*/
}

void BoxCollider::OnMouseRelease()
{
}

void BoxCollider::OnCollision(BoxCollider * other)
{
	gameObject->OnCollisionEnter(other);
}
