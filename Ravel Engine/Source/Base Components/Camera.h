#pragma once

#include "Color.h"
#include "RavelBehaviour.h"
#include "Transform.h"
#include "RavelRect.h"

class Camera : public RavelBehaviour {
public:
	Camera() {};
	virtual ~Camera() {};
	virtual Camera* Clone() {
		return Memory()->alloc<Camera>();
	}

	Matrix3x3 GetRenderPosition() {
		auto mat = transform->GetTransforms();
		mat.m[2] *= -1;
		mat.m[5] *= -1;
		return mat;
	}

	virtual void Start() override {};
	
	RavelRect size;
	Color background;
};