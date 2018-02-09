#pragma once

#include "RavelBehaviour.h"
#include "Transform.h"
#include "RavelRect.h"

class Collider2D : public RavelBehaviour {
public:
	Collider2D();
	virtual ~Collider2D();

	virtual void IntersectionTest(Collider2D* other) = 0;
	virtual void CursorIntersectionTest(Vector2 mouse) = 0;

protected:
	struct Circle {
		Vector2 Origin;
		float Radius;
	};
	sInt32 colManagerID;

public :
	Circle circle;
	RavelRect rect;
	size_t hashkey;
};