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
	//transform rect to local coordinates
	//calculate target origin first

	Vector2 bottom_left = v * rect->BottomLeft();

	//check target origin is withing bounds
	std::cout << "Target position: X " << bottom_left.x << ", Y " << bottom_left.y << std::endl;

	//try AABB first
	//bottom left
	if (bottom_left.x <= dimension.x && bottom_left.y <= dimension.y && bottom_left.x >= 0 && bottom_left.y >= 0) {
		// is inside box liao
		std::cout << "bottom_left collision" << std::endl;
		return true;
	}

	Vector2 top_left = v * rect->TopLeft();

	if (top_left.x <= dimension.x && top_left.y <= dimension.y && top_left.x >= 0 && top_left.y >= 0) {
		// is inside box liao
		std::cout << "top_left collision" << std::endl;
		return true;
	}

	Vector2 bottom_right = v * rect->BottomRight();

	if (bottom_right.x <= dimension.x && bottom_right.y <= dimension.y && bottom_right.x >= 0 && bottom_right.y >= 0) {
		// is inside box liao
		std::cout << "bottom_right collision" << std::endl;
		return true;
	}

	Vector2 top_right = v * rect->TopRight();

	if (top_right.x <= dimension.x && top_right.y <= dimension.y && top_right.x >= 0 && top_right.y >= 0) {
		// is inside box liao
		std::cout << "top_right collision" << std::endl;
		return true;
	}

	return false;
}

bool RavelRect::Intersect(Vector2 const& position) {
	Vector2 target_origin = v * position;

	//std::cout << "Target position: X " << target_origin.x << ", Y " << target_origin.y << std::endl;

	if (target_origin.x <= dimension.x && target_origin.y <= dimension.y && target_origin.x >= -dimension.x && target_origin.y >= -dimension.y) {
		return true;
	}
	return false;
}