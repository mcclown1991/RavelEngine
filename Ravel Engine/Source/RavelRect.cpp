#include "RavelRect.h"

RavelRect::RavelRect(Vector2 dimension) : dimension(dimension), origin(Vector2()) {
}

RavelRect::~RavelRect() {}

void RavelRect::Update(Vector2 x, Vector2 y, Vector2 origin) {

	Vector2 nX = x.Normalized();
	Vector2 nY = y.Normalized();

	r.m[0] = nX.x;	r.m[1] = nX.y;
	r.m[3] = nY.x;	r.m[4] = nY.y;

	this->origin = origin - (x * 0.5f) - (y * 0.5f);

	this->x = x;
	this->y = y;

	float dx = -nX * this->origin;
	float dy = -nY * this->origin;

	v.m[0] = nX.x;	v.m[1] = nX.y;	v.m[2] = dx;
	v.m[3] = nY.x;	v.m[4] = nY.y;	v.m[5] = dy;
	v.m[6] = 0;		v.m[7] = 0;		v.m[8] = 1;

	

}

bool RavelRect::Intersect(RavelRect* rect) {
	
	//try AABB first
	if (AABB(rect)) {
		return true;
	}
	
	//try obb
	if (OBB(rect)) {
		return true;
	}

	return false;
}

bool RavelRect::Intersect(Vector2 const& position) {
	//Vector2 target_origin = v * position;

	if (position.x <= BottomRight().x && position.y <= TopLeft().y && position.x >= BottomLeft().x && position.y >= BottomLeft().y) {
		return true;
	}
	return false;
}

bool RavelRect::AABB(RavelRect * other)
{
	if (BottomLeft().x < other->BottomRight().x &&
		BottomRight().x > other->BottomLeft().x &&
		BottomLeft().y < other->TopLeft().y &&
		TopLeft().y > other->BottomLeft().y)
		return true;
	else
		return false;

	////bottom left
	//if (bottom_left.x <= dimension.x && bottom_left.y <= dimension.y && bottom_left.x >= 0 && bottom_left.y >= 0) {
	//	// is inside box liao
	//	std::cout << "bottom_left collision" << std::endl;
	//	return true;
	//}

	//Vector2 top_left = other->TopLeft();

	//if (top_left.x <= dimension.x && top_left.y <= dimension.y && top_left.x >= 0 && top_left.y >= 0) {
	//	// is inside box liao
	//	std::cout << "top_left collision" << std::endl;
	//	return true;
	//}

	//Vector2 bottom_right = other->BottomRight();

	//if (bottom_right.x <= dimension.x && bottom_right.y <= dimension.y && bottom_right.x >= 0 && bottom_right.y >= 0) {
	//	// is inside box liao
	//	std::cout << "bottom_right collision" << std::endl;
	//	return true;
	//}

	//Vector2 top_right = other->TopRight();

	//if (top_right.x <= dimension.x && top_right.y <= dimension.y && top_right.x >= 0 && top_right.y >= 0) {
	//	// is inside box liao
	//	std::cout << "top_right collision" << std::endl;
	//	return true;
	//}

	return false;
}

bool RavelRect::OBB(RavelRect * other)
{
	// phase 1 : project to self axis 
	// check for projection direction
	// x-axis
	Vector2 top_left = v * other->TopLeft();
	Vector2 bottom_left = v * other->BottomLeft();
	Vector2 top_right = v * other->TopRight();
	Vector2 bottom_right = v * other->BottomRight();

	bool overlap = true;
	Vector2 v;
	bool tiltL = false;
	float result;

	// X = Axis
	if (top_left.x > bottom_left.x) {
		//tils to the right project bottom left and top right to x axis
		result = Projection(Vector2(0, 1), bottom_left, top_right);
		tiltL = false;
	}
	else {
		result = Projection(Vector2(0, 1), top_left, bottom_right);
		tiltL = true;
	}

	// check for separation
	if (tiltL) {
		if (top_left.x + result < TopLeft().x || top_left.x > TopRight().x)
			return false;
	}
	else {
		if (bottom_left.x > TopRight().x || top_right.x + result < TopLeft().x)
			return false;
	}
		
	// Y Axis
	if (top_left.y > top_right.y) {
		//tilt to the right
		result = Projection(Vector2(1, 0), top_left, bottom_right);
		tiltL = false;
	}
	else {
		result = Projection(Vector2(1, 0), top_right, bottom_left);
		tiltL = true;
	}

	// check for separation
	if (tiltL) {
		if (bottom_left.y > TopLeft().y || top_right.y < BottomLeft().y)
			return false;
	}
	else {
		if (bottom_right.y > TopLeft().y || top_left.y < BottomLeft().y)
			return false;
	}

	return true;
}

float RavelRect::Projection(Vector2 const & v, Vector2 const & p1, Vector2 const & p2)
{
	return v * (p2 - p1);
}
