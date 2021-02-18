#ifndef TEXT_H
#define TEXT_H

#include <string>
#include "RavelBehaviour.h"
#include "RectTransform.h"


class Text : public RavelBehaviour {
public:
	Text();
	virtual ~Text();
	virtual Text* Clone() {
		return Memory()->alloc<Text>();
	}

	virtual void LoadFromFile(std::string const& file);

	virtual void Start();
	virtual void OnDestory();

	void Render();

	void SetFontSize(size_t size);

	std::string _text;
	size_t size;
	RectTransform* rect;

private:
	std::string font;
};
#endif