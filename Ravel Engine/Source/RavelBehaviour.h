#pragma once

#include "Behaviour.h"

class RavelBehaviour : public Behaviour {
public:
	virtual void Start() {};
	virtual void Update() {};
	virtual void FixedUpdate() {};
	virtual void LateUpdate() {};
	virtual void OnDisable() {};
	virtual void OnEnable() {};
	virtual void OnDestory() {};

	virtual void OnCollisionEnter2D(Collider2D* other) {};
	virtual void OnCollisionExit2D(Collider2D* other) {};
	virtual void OnCollisionStay2D(Collider2D* other) {};

	virtual void OnMouseDown() {};
};