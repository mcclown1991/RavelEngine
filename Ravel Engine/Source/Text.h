#ifndef TEXT_H
#define TEXT_H

#include <string>
#include "Component.h"

class Text : public Component {
public:
	Text();
	virtual ~Text();

	virtual void OnStart();
	virtual void Update();
	virtual void OnDestory();

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