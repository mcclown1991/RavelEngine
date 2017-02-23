#ifndef SPRITE2D_H
#define SPRITE2D_H

#include "Component.h"
#include "sprite.h"
#include "Transform.h"

class Sprite2D : public Component{
public:
	Sprite2D();
	virtual ~Sprite2D();

	virtual void OnStart();
	virtual void Update();
	virtual void OnDestory();

	void CreateTexture(std::string , float , float );
	void Render();

private:
	Sprite** m_Sprite;
	rawTEXTURE* m_Texture;
	Vector2 m_Vertex[4];
	Matrix3x3 m_Reference_Frame;
};

#endif