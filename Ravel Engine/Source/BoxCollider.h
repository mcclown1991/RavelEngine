#ifndef BOXCOLLIDER_H
#define BOXCOLLIDER_H

#include <hgerect.h>
#include "Component.h"
#include "Transform.h"

class BoxCollider : public Component {
public:
	BoxCollider();
	virtual ~BoxCollider();

	virtual void OnStart();
	virtual void Update();
	virtual void OnDestory();

	void CreateBoxCollider(float width, float height);
	void OnMouseOver();
	void OnMouseClick();
	void OnMouseRelease();

	void OnCollision(BoxCollider* other);

	//delegates
	typedef void(*FunctionTrigger)();

	FunctionTrigger hover, click, release;

private:
	//hgeRect*	_Rect;
	float		_width;
	float		_height;
};
#endif
