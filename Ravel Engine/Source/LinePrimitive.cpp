#include "LinePrimitive.h"
#include "GraphicsManager.h"

LinePrimitive::LinePrimitive(){

}

LinePrimitive::~LinePrimitive(){

}

void LinePrimitive::Initialise(float x0, float y0, float x1, float y1){
	_x0 = x0;
	_x1 = x1;
	_y0 = y0;
	_y1 = y1;
	//_color = color;
	GetGraphicsManager()->AddLineBatch(this);
}


void LinePrimitive::Draw(){
	//use Gfx_RenderLine!!!
	//http://kvakvs.github.io/hge/doc/index.html
	Vector2 p0 = Vector2(_x0, _y0);
	Vector2 p1 = Vector2(_x1, _y1);
	//p0 = GetGFX()->GetViewTransform() * p0;
	//p1 = GetGFX()->GetViewTransform() * p1;
	//hge->Gfx_RenderLine(p0.x, p0.y, p1.x, p1.y, _color);
}