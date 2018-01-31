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

	enum Mode {
		SMALL = 0,
		LARGE
	};

	std::string text;
	int alignment;
	Mode mode;
	//DWORD color;

private:
	/*hgeFont* _small;
	hgeFont* _large;

	hgeFont* _render;*/
	
};
#endif