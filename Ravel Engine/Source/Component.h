#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>
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
	virtual Component* Clone() { return nullptr; }
	virtual void LoadFromFile(std::string const& stream) {}
	virtual void Serialise(){}

	//variables
	GameObject* gameObject;
	std::string tag;
	Transform* transform;
	bool IsActive;
	size_t CompID;
};

#endif