#include "Text.h"
#include "Font.h"
#include "RavelEngine.h"


Text::Text() : rect(nullptr)
{
}

Text::~Text()
{
}

void Text::Start()
{
	GetGraphicsManager()->AddText(this);
	font = "font1"; // defualt font
	rect = factory()->CreateComponent<RectTransform>();
	size = 100;
}

void Text::OnDestory()
{
	if (rect)
		rect->OnDestory();
	this->~Text();
}

void Text::Render()
{
	Vector2 position = rect->position;
	for(char ch : _text){
		FontSystem::font f = GetFontManager()->FetchFont(font, ch);
		rect->position.x += rect->hscale;
		Vector2 uv = Vector2(((float)f.x / (float)f.sz), ((float)f.y / (float)f.sy));
		Vector2 scale = Vector2(((float)f.l/ (float)f.sz), ((float)f.h / (float)f.sy));
		rect->hscale = scale.x * size;
		rect->vscale = scale.y * size;
		GetGraphicsManager()->Renderer()->Render(f.sampleid, rect->GetLocalTransforms(), uv, scale, true, 1);
	}

	rect->SetPosition(position);
}

void Text::SetFontSize(size_t size)
{
	this->size = size * 10;
}
