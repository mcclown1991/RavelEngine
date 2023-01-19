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
		return transform->GetTransforms().Transpose();
	}

	RavelRect size;
	Color background;
};