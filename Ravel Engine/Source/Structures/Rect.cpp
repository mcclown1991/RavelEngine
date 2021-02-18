#include "Rect.h"

bool Rect::Contain(Vector2 const& point) {
	//do AABB test
	if (point.x > x || point.x < x + xMax) {// within x
		if (point.y > y || point.y < y + yMax)
			return true;
	}
	return false;
}

bool Rect::Overlaps(Rect const & other)
{
	if (Contain(Vector2(other.x, other.y)) || Contain(Vector2(other.xMax, other.yMax))
		|| Contain(Vector2(other.x, other.yMax)) || Contain(Vector2(other.xMax, other.y)))
		return true;
	return false;
}

void Rect::Set(float x, float y, float width, float height)
{
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
}
