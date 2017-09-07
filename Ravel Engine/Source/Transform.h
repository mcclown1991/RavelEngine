#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "Component.h"
#include "Matrix3x3.h"

class Transform : public Component{
public:
	Transform();
	virtual ~Transform();

	virtual void OnStart();
	virtual void Update();
	virtual void OnDestory();

	void SetPosition(Vector2);

	Vector2 GetPosition();
	Matrix3x3 GetTransforms();
	Matrix3x3 GetLocalTransforms();

	//Public Functions
	Vector2 up;
	Vector2 right;
	Vector2 position;
	float localEulerAngles;
	float hscale, vscale;

	//Transform Functions
	void Rotate(float angle);
	void Scale(float scale);
};

#endif