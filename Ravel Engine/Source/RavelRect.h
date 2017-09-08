#pragma once

#include "Vector2.h"
#include "Matrix3x3.h"

class RavelRect {
public:
	RavelRect(Vector2 x, Vector2 y, Vector2 origin);
	~RavelRect();

	bool Intersect(RavelRect* rect);
	bool Intersect(Vector2 const& position);

	Vector2 x, y, origin;

	Matrix3x3 v;
};