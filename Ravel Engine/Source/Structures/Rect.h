#pragma once
#include "RavelMath.h"

struct Rect {
public:
	Rect() {}

	// Propeties
	Vector2 center;
	float height;
	float max;
	float min;
	Vector2 position;
	Vector2 size;
	float width;
	float x;
	float xMax;
	float xMin;
	float y;
	float yMax;
	float yMin;

	bool Contain(Vector2 const& point);
	bool Overlaps(Rect const& other);
	void Set(float x, float y, float width, float height);
};