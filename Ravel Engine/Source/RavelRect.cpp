#include "RavelRect.h"

RavelRect::RavelRect(Vector2 dimension) : dimension(dimension), origin(Vector2()) {
	dimension.x *= 0.5f;
	dimension.y *= 0.5f;
}

RavelRect::~RavelRect() {}

void RavelRect::Update(Vector2 x, Vector2 y, Vector2 origin) {

	this->x = x;
	this->y = y;

	Vector2 nX = x.Normalized();
	Vector2 nY = y.Normalized();

	float dx = -nX * origin;
	float dy = -nY * origin;

	v.m[0] = nX.x;	v.m[1] = nX.y;	v.m[2] = dx;
	v.m[3] = nY.x;	v.m[4] = nY.y;	v.m[5] = dy;
	v.m[6] = 0;		v.m[7] = 0;		v.m[8] = 1;

	r.m[0] = nX.x;	r.m[1] = nX.y;
	r.m[3] = nY.x;	r.m[4] = nY.y;

	this->origin.x = origin.x;
	this->origin.y = origin.y;
}

bool RavelRect::Intersect(RavelRect* rect) {
	//transform rect to local coordinates
	//calculate target origin first

	Vector2 target_origin = v * rect->origin;

	//check target origin is withing bounds
	std::cout << "Target position: X " << target_origin.x << ", Y " << target_origin.y << std::endl;

	if (target_origin.x <= dimension.x && target_origin.y <= dimension.y && target_origin.x >= -dimension.x && target_origin.y >= -dimension.y) {
		// is inside box liao
		std::cout << "Origin collision" << std::endl;
		return true;
	}

	Vector2 up = target_origin + (r * rect->y);
	if (-up.x <= dimension.x && up.y <= dimension.y && -up.x >= -dimension.x && up.y >= -dimension.y) {
		// is inside box liao
		std::cout << "Up vector collision" << std::endl;
		return true;
	}
	
	
	Vector2 right = target_origin - (r * rect->x);
	
	

	if (-right.x <= dimension.x && right.y <= dimension.y && -right.x >= -dimension.x && right.y >= -dimension.y) {
		// is inside box liao
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