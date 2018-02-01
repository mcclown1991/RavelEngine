#include "Transform.h"

Transform::Transform() : RavelBehaviour(), up(0, 1), right(1, 0), position(0, 0), localEulerAngles(0.f), hscale(1.f), vscale(1.f), parent(nullptr){
}

Transform::~Transform(){

}

void Transform::SetPosition(Vector2 position){
	this->position = position;
}

Vector2 Transform::GetPosition()
{
	if(parent)
		return parent->position + position;
	return position;
}

Matrix3x3 Transform::GetTransforms()
{
	Matrix3x3 transforms;

	transforms.m[0] = right.x * hscale;
	transforms.m[1] = up.x * vscale;
	transforms.m[3] = right.y * hscale;
	transforms.m[4] = up.y * vscale;

	transforms.m[2] = position.x * 0.89f;
	transforms.m[5] = position.y * 0.89f;

	if(parent)
		return parent->GetTransforms() * transforms;
	return transforms;
}

Matrix3x3 Transform::GetLocalTransforms() {
	Matrix3x3 transforms;

	transforms.m[0] = right.x * hscale;
	transforms.m[1] = up.x * vscale;
	transforms.m[3] = right.y * hscale;
	transforms.m[4] = up.y * vscale;

	transforms.m[2] = position.x * 0.89f;
	transforms.m[5] = position.y * 0.89f;

	return transforms;
}

void Transform::Rotate(float angle)
{
	angle = (3.14125f / 180.0f) * angle;
	localEulerAngles += angle;
	up = Vector2(-sin(localEulerAngles), cos(localEulerAngles));
	right = Vector2(up.y, -up.x);
}

void Transform::Scale(float scale)
{
	this->hscale = scale;
	this->vscale = scale;
}
