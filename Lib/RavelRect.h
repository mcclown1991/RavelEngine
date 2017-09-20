#pragma once

#include "Vector2.h"
#include "Matrix3x3.h"

class RavelRect {
public:
	RavelRect(Vector2 dimension);
	~RavelRect();

	void Update(Vector2 x, Vector2 y, Vector2 origin);
	bool Intersect(RavelRect* rect);
	bool Intersect(Vector2 const& position);

	Vector2 dimension, origin;
	Vector2 x, y;

	Matrix3x3 v, r;
};