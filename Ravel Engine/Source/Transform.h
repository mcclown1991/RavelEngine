#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "RavelBehaviour.h"
#include "Matrix3x3.h"

class Transform : public RavelBehaviour {
public:
	Transform();
	virtual ~Transform();
	virtual Transform* Clone() {
		return Memory()->alloc<Transform>();
	}

	virtual void OnDestory() { this->~Transform(); }

	void SetPosition(Vector2);

	Vector2 GetPosition();
	Matrix3x3 GetTransforms();
	Matrix3x3 GetLocalTransforms();

	//Public Functions
	Vector2 up;
	Vector2 right;
	Vector2 position;
	Vector2 localposition;
	float localEulerAngles;
	float hscale, vscale;
	Transform* parent;

	//Transform Functions
	void Rotate(float angle);
	void Scale(float scale);
};

#endif