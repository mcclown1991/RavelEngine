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

	void SetFontSize(size_t size);

	std::string _text;
	size_t size;

private:
	std::string font;
	Transform* local;
};
#endif