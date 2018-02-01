#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>
#include "MemoryManager.h"
#include "RavelObject.h"

//Data Types for components
template <typename T>
using RavelAction = void(T::*)();

class GameObject;
class Transform;

class Component : public RavelObject {
public:
	Component();
	virtual ~Component();
	virtual Component* Clone() {
		return Memory()->alloc<Component>();
	}

	//variables
	GameObject* gameObject;
	std::string tag;
	Transform* transform;
	bool IsActive;
	size_t CompID;
};

#endif