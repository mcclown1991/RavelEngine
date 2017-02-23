#include "Transform.h"

Transform::Transform() : Component(), up(0, 1), position(0, 0), localEulerAngles(0.f), hscale(1.f), vscale(1.f){
}

Transform::~Transform(){

}

void Transform::OnStart(){
	
}

void Transform::Update(){

}

void Transform::OnDestory(){

}

void Transform::SetPosition(Vector2 position){
	this->position = position;
}

Vector2 Transform::GetPosition()
{
	return parent == nullptr ? position : parent->position + position;
}

Matrix3x3 Transform::GetTransforms()
{
	Matrix3x3 transforms;
	float cosine = cosf(localEulerAngles);
	float sine = sinf(localEulerAngles);
	transforms.m[0] = cosine * hscale;
	transforms.m[1] = -sine * hscale;
	transforms.m[3] = sine * vscale;
	transforms.m[4] = cosine * vscale;

	transforms.m[2] = position.x;
	transforms.m[5] = position.y;

	return parent == nullptr ? transforms : parent->GetTransforms() * transforms;
}

void Transform::Rotate(float angle)
{
	angle = (3.14125f / 180.0f) * angle;
	localEulerAngles += angle;
	up = Vector2(-sin(localEulerAngles), cos(localEulerAngles));
}

void Transform::Scale(float scale)
{
	this->hscale = scale;
	this->vscale = scale;
}
