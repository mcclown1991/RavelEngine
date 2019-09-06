#include "Component.h"
#include "Transform.h"

Component::Component() : gameObject(nullptr), tag(), transform(nullptr), IsActive(true){
	
}

Component::~Component(){
	if (transform)
		transform->OnDestory();
}