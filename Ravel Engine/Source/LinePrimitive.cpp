#include "LinePrimitive.h"
#include "GraphicsManager.h"

LinePrimitive::LinePrimitive(){

}

LinePrimitive::~LinePrimitive(){

}

void LinePrimitive::OnStart(){

}

void LinePrimitive::Update(){

}

void LinePrimitive::OnDestory(){

}

void LinePrimitive::Initialise(float x0, float y0, float x1, float y1, DWORD color){
	_x0 = x0;
	_x1 = x1;
	_y0 = y0;
	_y1 = y1;
	_color = color;
	GetGFX()->AddLineBatch(this);
}


void LinePrimitive::Draw(HGE* hge){
	//use Gfx_RenderLine!!!
	//http://kvakvs.github.io/hge/doc/index.html
	hge->Gfx_RenderLine(_x0, _y0, _x1, _y1, _color);
}