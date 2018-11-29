#pragma once

#include "RavelBehaviour.h"

class Canvas : public RavelBehaviour {
public:
	Canvas();
	virtual ~Canvas();
	virtual Canvas* Clone() {
		return Memory()->alloc<Canvas>();
	}

	virtual void LoadFromFile(std::string const& file);

	virtual void OnDestory() { this->~Canvas(); }
	

};