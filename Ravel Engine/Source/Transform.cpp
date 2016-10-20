#include "Transform.h"

Transform::Transform() : Component(), position(0, 0){

}

Transform::~Transform(){

}

void Transform::OnStart(){
	
}

void Transform::Update(){

}

void Transform::OnDestory(){

}

void Transform::SetPosition(fVector2 position){
	this->position = position;
}

fVector2 Transform::GetPosition()
{
	return parent == nullptr ? position : parent->position + position;
}
