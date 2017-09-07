#include "BoxCollider.h"
#include "RavelEngine.h"
#include "CollisionManager.h"
#include "Input.h"

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
	GetCollision()->AddCollider(this);
	_rect = new RavelRect(gameObject->transform->right * _width, gameObject->transform->up * _height, gameObject->transform->position);
}

void BoxCollider::CreateBoxCollider(float width, float height)
{
	_width = width;
	_height = height;
	GetCollision()->AddCollider(this);
	_rect = new RavelRect(gameObject->transform->right * _width, gameObject->transform->up * _height, gameObject->transform->position);
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

void BoxCollider::OnCollision2D(Collider2D * other)
{
	gameObject->OnCollisionEnter2D(other);
}

void BoxCollider::IntersectionTest(Collider2D* other) {

}

void BoxCollider::CursorIntersectionTest(Vector2 mouse) {
	//do position testing remeber mouse position is in screen space
	//convert mouse to world space
	if (_rect->Intersect(mouse)) {
		gameObject->OnMouseHover();
		std::cout << "BoxCollider: OnMouseHover()" << std::endl;
	}
}
