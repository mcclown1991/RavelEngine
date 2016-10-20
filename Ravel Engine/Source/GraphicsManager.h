#ifndef GRAPHICSMANAGER_H
#define GRAPHICSMANAGER_H

#include <list>
#include <map>
#include <algorithm>
#include "DataType.h"
#include "Sprite2D.h"
#include "GameObject.h"
#include "Text.h"
#include "LinePrimitive.h"

class GraphicsManager
{
public:
	GraphicsManager();
	sInt32 AddSprite(Sprite2D* m_sprite);
	bool RemoveSprite(sInt32 index);

	sInt32 AddText(Text* _txt);

	sInt32 AddLineBatch(LinePrimitive* _line);

	Sprite** CreateTexture(std::string const& filepath, float width, float height);

	bool ClearSprite();

	bool Render();

	void OnExit();

private:
	std::list<Sprite2D *>spriteList;
	std::list<Text *>textList;
	std::list<LinePrimitive *>lineList;

	std::map<std::string, Sprite*> _Textures;
};

GraphicsManager* GetGFX();

#endif