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

	//virtual void OnStart();
	//virtual void Update();
	//virtual void OnDestory();

	//virtual void SetActive(bool isactive);

	//variables
	GameObject* gameObject;
	std::string tag;
	Transform* parent;
	Transform* transform;
	bool IsActive;
	size_t CompID;
};

#endif