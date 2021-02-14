#include "RectTransform.h"

RectTransform::RectTransform() : Transform() {
}

RectTransform::~RectTransform() {
}

void RectTransform::Start() {
}

void RectTransform::OnDestory() {
	this->~RectTransform();
}
