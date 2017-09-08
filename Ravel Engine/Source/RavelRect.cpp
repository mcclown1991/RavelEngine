#include "RavelRect.h"

RavelRect::RavelRect(Vector2 x, Vector2 y, Vector2 origin) : x(x), y(y), origin(origin) {
	Vector2 nX = x.Normalized();
	Vector2 nY = y.Normalized();
	v.m[0] = nX.x;	v.m[1] = nY.x;	v.m[2] = origin.x;
	v.m[3] = nX.y;	v.m[4] = nY.y;	v.m[5] = origin.y;
	v.m[6] = 0;		v.m[7] = 0;		v.m[8] = 1;
}

RavelRect::~RavelRect() {}

bool RavelRect::Intersect(RavelRect* rect) {
	//transform rect to local coordinates
	//calculate target origin first

	Vector2 target_origin = v * rect->origin;

	//check target origin is withing bounds

	if (target_origin.x <= x.x || target_origin.y <= y.y) {

	}

	return false;
}

bool RavelRect::Intersect(Vector2 const& position) {
	Vector2 target_origin = v * position;

	//std::cout << "Target position: X " << target_origin.x << ", Y " << target_origin.y << std::endl;

	if (target_origin.x <= x.x && target_origin.y <= y.y && target_origin.x >= origin.x && target_origin.y >= origin.y) {
		return true;
	}
	return false;
}