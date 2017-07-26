#ifndef GRAPHICSMANAGER_H
#define GRAPHICSMANAGER_H

#include <list>
#include <map>
#include <algorithm>
#include "DataType.h"
#include "Matrix3x3.h"
#include "Sprite2D.h"
#include "GameObject.h"
#include "Text.h"
#include "LinePrimitive.h"
#include "GraphicsAPI.h"

class GraphicsManager
{
public:
	GraphicsManager();

	void InitialiseGraphicsManager(Graphics* render);

	sInt32 AddSprite(Sprite2D* m_sprite);
	bool RemoveSprite(sInt32 index);

	sInt32 AddText(Text* _txt);

	sInt32 AddLineBatch(LinePrimitive* _line);

	//Sprite** CreateTexture(std::string const& filepath, float width, float height);

	unsigned CreateTexture(std::string const& filepath);

	bool ClearSprite();

	bool Render();

	void OnExit();

	Matrix3x3 const& GetViewTransform() const;

	HRESULT SetVertexShader(std::string const& file);
	HRESULT SetFragmentShader(std::string const& file);

	Graphics* Renderer() { return renderer; }

private:
	Graphics* renderer;

	std::list<Sprite2D *>spriteList;
	std::list<Text *>textList;
	std::list<LinePrimitive *>lineList;

	//std::map<std::string, Sprite*> _Textures;
	Matrix3x3 _viewTransform;
	//HGE* hge;
};

GraphicsManager* GetGraphicsManager();

#endif