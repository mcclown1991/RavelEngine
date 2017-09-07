#ifndef RAVELOBJECT_H
#define RAVELOBJECT_H

#include <string>
#include <functional>
#include "DataType.h"

class Collider2D;

class RavelObject{
public:
	RavelObject() {};
	virtual ~RavelObject() {};

	// Component must have functions
	
	virtual void OnStart() = 0;
	virtual void Update() = 0;
	virtual void OnDestory() = 0;

	virtual void OnMouseDown() {}
	virtual void OnMouseHover() {}

	virtual void OnCollisionEnter2D(Collider2D*) {}

	virtual std::size_t GetInstanceID() {
		return instanceID(name);
	}

	std::string name;

private:
	std::hash<std::string> instanceID;

};

#endif
