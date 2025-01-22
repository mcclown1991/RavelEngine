#pragma once

#include "Vector2.h"
#include "Matrix3x3.h"

class RavelRect {
public:
	RavelRect() {};
	RavelRect(Vector2 dimension);
	~RavelRect();

	void Update(Vector2 x, Vector2 y, Vector2 origin);
	bool Intersect(RavelRect* rect);
	bool Intersect(Vector2 const& position);

	Vector2 dimension, origin;
	Vector2 x, y;

	Matrix3x3 v, r;

	Vector2 TopLeft() {
		return origin + y;
	}

	Vector2 TopRight() {
		return origin + x + y;
	}

	Vector2 BottomLeft() {
		return origin;
	}

	Vector2 BottomRight() {
		return origin + x;
	}

private:
	bool AABB(RavelRect* other);
	bool OBB(RavelRect* other);
	float Projection(Vector2 const& v, Vector2 const& p1, Vector2 const& p2);
};