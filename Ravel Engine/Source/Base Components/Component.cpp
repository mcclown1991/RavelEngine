#include "Component.h"

#include "GameObject.h"
#include "Transform.h"

Component::Component() : gameObject(nullptr), tag(), transform(nullptr), IsActive(true){
	
}

Component::~Component(){
	if (transform)
		transform->OnDestory();
}

size_t Component::GetInstanceID() {
	return gameObject ? gameObject->GetInstanceID() : RavelObject::GetInstanceID();
}
