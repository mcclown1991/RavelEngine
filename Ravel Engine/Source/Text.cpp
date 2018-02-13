#include "Text.h"
#include "Font.h"
#include "RavelEngine.h"


Text::Text()
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
	size = 10;
}

void Text::OnDestory()
{
	if (rect)
		rect->OnDestory();
	this->~Text();
}

void Text::Render()
{
	Vector2 prev(0, 0);
	Vector2 position = rect->position;
	for(char ch : _text){
		FontSystem::font f = GetFontManager()->FetchFont(font, ch);
		prev = Vector2(f.l, f.h);
		rect->position.x += prev.x;
		Vector2 uv = Vector2((f.x / f.sz), (f.y / f.sy));
		Vector2 scale = Vector2((f.l/ f.sz), (f.h / f.sy));
		rect->hscale = scale.x * size * 10;
		rect->vscale = scale.y * size * 10;
		GetGraphicsManager()->Renderer()->Render(f.sampleid, rect->GetLocalTransforms(), uv, scale, true, 1);
	}

	rect->SetPosition(position);
}

void Text::SetFontSize(size_t size)
{
	this->size = size;
}
