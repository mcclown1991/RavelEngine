#ifndef LINEPRIMITIVE
#define LINEPRIMITIVE

#include "RavelBehaviour.h"
#include "Transform.h"

class LinePrimitive : public RavelBehaviour{
public :
	LinePrimitive();
	virtual ~LinePrimitive();
	virtual LinePrimitive* Clone() {
		return Memory()->alloc<LinePrimitive>();
	}

	virtual void OnDestory();

	void Initialise(float x0, float y0, float x1, float y1);
	void Draw();

private:
	float _x0, _x1, _y0, _y1;
	//DWORD _color;
};
#endif