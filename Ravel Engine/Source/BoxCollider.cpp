#include "BoxCollider.h"
#include "RavelEngine.h"
#include "CollisionManager.h"
#include "Input.h"

BoxCollider::BoxCollider() : hover(nullptr), click(nullptr), release(nullptr)
{
	std::cout << "Creating new Box Collider" << std::endl;
}

BoxCollider::~BoxCollider()
{
}

void BoxCollider::Update()
{
	rect.Update(gameObject->transform->right * _width, gameObject->transform->up * _height, gameObject->transform->position);
	GetCollision()->UpdateCollider(colManagerID);
}

void BoxCollider::OnDestory()
{
	this->~BoxCollider();
}

void BoxCollider::CreateBoxCollider() {

	Sprite2D* sp = gameObject->GetComponent<Sprite2D>();
	if (sp != nullptr) {
		_width = sp->m_Dimension.x;
		_height = sp->m_Dimension.y;
	}
	else {
		_width = gameObject->transform->hscale;
		_height = gameObject->transform->vscale;
	}
	
	rect = RavelRect(Vector2(_width, _height));
	colManagerID = GetCollision()->AddCollider(this);
}

void BoxCollider::CreateBoxCollider(float width, float height)
{
	_width = width;
	_height = height;
	
	rect = RavelRect(Vector2(_width, _height));
	colManagerID = GetCollision()->AddCollider(this);
}

void BoxCollider::OnMouseOver()
{
	
}

void BoxCollider::OnMouseClick()
{

}

void BoxCollider::OnMouseRelease()
{
}

void BoxCollider::OnCollision2D(Collider2D * other)
{
	//gameObject->OnCollisionEnter2D(other);
}

bool BoxCollider::IntersectionTest(Collider2D* other) {

	if (rect.Intersect(&(other->rect))) {
		//gameObject->OnCollisionEnter2D(other);
		//other->gameObject->OnCollisionEnter2D(this);
		std::cout << gameObject->name << " :: " << "BoxCollider: OnCollisionEnter()" << "->" << other->gameObject->name << std::endl;
		return true;
	}
	return false;
}

bool BoxCollider::CursorIntersectionTest(Vector2 mouse) {
	//do position testing remeber mouse position is in screen space
	//convert mouse to world space
	if (rect.Intersect(mouse)) {
		//gameObject->OnMouseHover();
		//std::cout << gameObject->name << " :: " << "BoxCollider: OnMouseHover()" << std::endl;
		if (GetMouseButtonDown(0))
			std::cout << gameObject->name << " :: " << "BoxCollider: OnMouseDown()" << std::endl;

		return true;
	}
	return false;
}
