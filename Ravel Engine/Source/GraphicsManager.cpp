#include "GraphicsManager.h"
#include "RavelEngine.h"

GraphicsManager::GraphicsManager()
{
	sInt32 height = RavelEngine::GetRavelEngine()->GetScreenHeight();
	_viewTransform.Mtx33Identity();
	_viewTransform.m[4] = -1;
	_viewTransform.m[5] = (float)height;
	//Mtx3x3Inverse(&_viewTransform);

	hge = RavelEngine::GetRavelEngine()->GetHGE();
}

GraphicsManager* GetGFX()
{
	static GraphicsManager s;
	return(&s);
}

sInt32 GraphicsManager::AddSprite(Sprite2D* m_sprite)
{
	spriteList.push_back(m_sprite);
	return spriteList.size() - 1;
}

sInt32 GraphicsManager::AddText(Text* _txt) {
	textList.push_back(_txt);
	return textList.size() - 1;
}

sInt32 GraphicsManager::AddLineBatch(LinePrimitive* _line){
	lineList.push_back(_line);
	return lineList.size() - 1;
}

Sprite** GraphicsManager::CreateTexture(std::string const& filepath, float width, float height){
	if (_Textures.count(filepath) == 0){
		
		rawTEXTURE tex = hge->Texture_Load(filepath.c_str());
		Sprite* sp = new Sprite(&tex, width, height);
		_Textures[filepath] = sp;
	}

	return &_Textures[filepath];
}

bool GraphicsManager::RemoveSprite(sInt32 index)
{
	std::list<Sprite2D *>::iterator iter = spriteList.begin();
	std::advance(iter, index);
	spriteList.erase(iter);
	return true;
}

bool GraphicsManager::ClearSprite()
{
	spriteList.clear();
	return true;
}

bool GraphicsManager::Render()
{

	std::for_each(spriteList.begin(), spriteList.end(), [](Sprite2D* _sprite)
	{
		if (_sprite->IsActive)
		_sprite->Render();
	});

	std::for_each(textList.begin(), textList.end(), [](Text* _text)
	{
		if (_text->IsActive)
			_text->Render();
	});

	std::for_each(lineList.begin(), lineList.end(), [](LinePrimitive* _line)
	{
		if (_line->IsActive)
			_line->Draw(RavelEngine::GetRavelEngine()->GetHGE());
	});

	return true;
}

void GraphicsManager::OnExit()
{
	ClearSprite();
	
	std::for_each(_Textures.begin(), _Textures.end(), [](std::pair<std::string, Sprite*> iter) {
		delete iter.second;

	});
	_Textures.clear();

	spriteList.clear();
	textList.clear();
	lineList.clear();
}


Matrix3x3 const& GraphicsManager::GetViewTransform() const{
	return _viewTransform;
}