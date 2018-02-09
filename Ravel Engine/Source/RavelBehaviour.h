#pragma once

#include "Behaviour.h"

class Collider2D;
class RavelBehaviour : public Behaviour {
public:
	RavelBehaviour() {};
	virtual ~RavelBehaviour() { std::cout << "Ravel destructor" << std::endl; };

	virtual void Start() {};
	virtual void Update() {};
	virtual void FixedUpdate() {};
	virtual void LateUpdate() {};
	virtual void OnDisable() {};
	virtual void OnEnable() {};
	virtual void OnDestory() {};

	// Collision Functions
	virtual void OnCollisionEnter2D(Collider2D* other) {};
	virtual void OnCollisionExit2D(Collider2D* other) {};
	virtual void OnCollisionStay2D(Collider2D* other) {};

	virtual void OnTriggerEnter2D(Collider2D* other) {};
	virtual void OnTriggerExit2D(Collider2D* other) {};
	virtual void OnTriggerStay2D(Collider2D* other) {};

	virtual void OnMouseDown() {};
	virtual void OnMouseDrag() {};
	virtual void OnMouseEnter() {};
	virtual void OnMouseExit() {};
	virtual void OnMouseOver() {};
	virtual void OnMouseUp() {};

	virtual RavelBehaviour* Clone() { return nullptr; }
};