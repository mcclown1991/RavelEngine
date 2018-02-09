#ifndef TEXT_H
#define TEXT_H

#include <string>
#include "RavelBehaviour.h"

class Text : public RavelBehaviour {
public:
	Text();
	virtual ~Text();
	virtual Text* Clone() {
		return Memory()->alloc<Text>();
	}

	virtual void Start();

	void Render();

	std::string text;
	int alignment;
	//DWORD color;

private:
	/*hgeFont* _small;
	hgeFont* _large;

	hgeFont* _render;*/
	
};
#endif