#include "Canvas.h"

Canvas::Canvas() : RavelBehaviour() {
}

Canvas::~Canvas() {
}

void Canvas::LoadFromFile(std::string const & file) {
}

void Canvas::OnDestory() {
	this->~Canvas();
}