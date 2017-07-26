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

	void CreateTexture(std::string filename, float width, float height);
	void Render();

private:
	Transform* m_Model;
	unsigned m_SampleID;
	//rawTEXTURE* m_Texture;
	Vector2 m_UV;
	Vector2 m_Size;
	Matrix3x3 m_Reference_Frame;
};

#endif