#ifndef SPRITE2D_H
#define SPRITE2D_H

#include "RavelBehaviour.h"
#include "sprite.h"
#include "Transform.h"

class Sprite2D : public RavelBehaviour{
public:
	Sprite2D();
	virtual ~Sprite2D();
	virtual Sprite2D* Clone() {
		return Memory()->alloc<Sprite2D>();
	}

	virtual void Update();
	virtual void Destory();

	void CreateTexture(std::string filename, float width, float height);
	void Render();

	Vector2 m_Dimension;

private:
	Transform* m_Model;
	unsigned m_SampleID;
	//rawTEXTURE* m_Texture;
	Vector2 m_UV;
	Vector2 m_Size;

	
};

#endif