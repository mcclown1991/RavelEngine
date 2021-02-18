#pragma once
#include "Transform.h"
#include "Stuctures.h"

class RectTransform : public Transform {
public:
	RectTransform();
	virtual ~RectTransform();
	virtual RectTransform* Clone() {
		return Memory()->alloc<RectTransform>();
	}

	virtual void Start();
	virtual void OnDestory();

	// properties
	Rect rect;
};