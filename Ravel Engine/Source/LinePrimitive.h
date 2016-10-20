#ifndef LINEPRIMITIVE
#define LINEPRIMITIVE

#include "Component.h"
#include "Transform.h"

class LinePrimitive : public Component{
public :
	LinePrimitive();
	virtual ~LinePrimitive();

	virtual void OnStart();
	virtual void Update();
	virtual void OnDestory();

	void Initialise(float x0, float y0, float x1, float y1, DWORD color);
	void Draw(HGE* hge);

private:
	float _x0, _x1, _y0, _y1;
	DWORD _color;
};
#endif