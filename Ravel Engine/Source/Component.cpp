#include "Component.h"

Component::Component() : gameObject(nullptr), tag(), parent(nullptr), transform(nullptr), IsActive(true){
	
}

Component::~Component(){
	
}

void Component::OnStart(){

}

void Component::Update(){

}

void Component::OnDestory(){

}

void Component::SetActive(bool isactive){
	IsActive = isactive;
}