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
	this->~RectTransform();
}
