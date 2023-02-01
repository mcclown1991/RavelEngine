#include "Transform.h"

Transform::Transform() : RavelBehaviour(), up(0, 1, 1), right(1, 0, 1), position(0, 0, 1), localEulerAngles(0.f), hscale(1.f), vscale(1.f), parent(nullptr){
}

Transform::~Transform(){
}

void Transform::OnDestory() {
	this->~Transform();
}

void Transform::SetPosition(Vector3 const& position) {
	this->position = position;
}

void Transform::SetLocalPosition(Vector3 const& position) {
	if (!parent)
		this->position = position;
	this->localposition = position;
}

Vector3 Transform::GetPosition() {
	if(parent)
		return parent->GetPosition() + localposition;
	return position;
}

Vector3 Transform::GetLocalPosition() {
	if (!parent)
		return position;
	return localposition;
}


Matrix3x3 Transform::GetTransforms() {
	Matrix3x3 transforms;

	transforms.m[0] = right.x * hscale;
	transforms.m[1] = up.x * vscale;
	transforms.m[3] = right.y * hscale;
	transforms.m[4] = up.y * vscale;

	auto pos = GetPosition();
	transforms.m[2] = pos.x /** 0.89f*/;
	transforms.m[5] = pos.y /** 0.89f*/;

	return transforms;
}

Matrix3x3 Transform::GetLocalTransforms() {
	Matrix3x3 transforms;

	transforms.m[0] = right.x * hscale;
	transforms.m[1] = up.x * vscale;
	transforms.m[3] = right.y * hscale;
	transforms.m[4] = up.y * vscale;

	transforms.m[2] = localposition.x;
	transforms.m[5] = localposition.y;

	return transforms;
}

void Transform::Rotate(float angle) {
	angle = (3.14125f / 180.0f) * angle;
	localEulerAngles += angle;
	up = Vector2(-sin(localEulerAngles), cos(localEulerAngles));
	right = Vector2(up.y, -up.x);
}

void Transform::Scale(float scale) {
	this->hscale = scale;
	this->vscale = scale;
}
