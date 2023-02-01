#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "RavelBehaviour.h"
#include "Matrix3x3.h"
#include "Vector3.h"

class Transform : public RavelBehaviour {
public:
	Transform();
	virtual ~Transform();
	virtual Transform* Clone() {
		return Memory()->alloc<Transform>();
	}

	virtual void OnDestory();

	void SetPosition(Vector3 const&);
	void SetLocalPosition(Vector3 const&);

	Vector3 GetPosition();
	Vector3 GetLocalPosition();
	Matrix3x3 GetTransforms();
	Matrix3x3 GetLocalTransforms();

	//Public Functions
	Vector3 up;
	Vector3 right;
	Vector3 position;
	Vector3 localposition;
	float localEulerAngles;
	float hscale, vscale;
	Transform* parent;

	//Transform Functions
	void Rotate(float angle);
	void Scale(float scale);
};

#endif