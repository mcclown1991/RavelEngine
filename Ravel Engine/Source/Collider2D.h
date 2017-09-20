#pragma once

#include "Component.h"
#include "Transform.h"

class Collider2D : public Component {
public:
	Collider2D();
	virtual ~Collider2D();

	virtual void OnStart() {};
	virtual void Update() {};
	virtual void OnDestory() {};

	virtual void OnMouseOver() {};
	virtual void OnMouseClick() {};
	virtual void OnMouseRelease() {};

	virtual void OnCollision2D(Collider2D* other) {};

	virtual void IntersectionTest(Collider2D* other) = 0;
	virtual void CursorIntersectionTest(Vector2 mouse) = 0;

protected:
	struct Circle {
		Vector2 Origin;
		float Radius;
	};

public :
	Circle circle;
	bool isRect;
};