#ifndef BOXCOLLIDER_H
#define BOXCOLLIDER_H

#include "Collider2D.h"
#include "RavelRect.h"

class BoxCollider : public Collider2D {
public:
	BoxCollider();
	virtual ~BoxCollider();

	virtual void OnStart();
	virtual void Update();
	virtual void OnDestory();

	void CreateBoxCollider();
	void CreateBoxCollider(float width, float height);
	virtual void OnMouseOver();
	virtual void OnMouseClick();
	virtual void OnMouseRelease();

	virtual void OnCollision2D(Collider2D* other);

	virtual void IntersectionTest(Collider2D* other);
	virtual void CursorIntersectionTest(Vector2 mouse);

	//delegates
	typedef void(*FunctionTrigger)();

	FunctionTrigger hover, click, release;

private:
	//hgeRect*	_Rect;
	float		_width;
	float		_height;
	RavelRect*	_rect;
};
#endif
