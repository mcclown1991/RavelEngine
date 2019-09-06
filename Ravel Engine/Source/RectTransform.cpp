#include "RectTransform.h"

RectTransform::RectTransform()
{
}

RectTransform::~RectTransform()
{
}

void RectTransform::Start()
{
}

void RectTransform::OnDestory()
{
	Memory()->dealloc(this);
	this->~RectTransform();
}
