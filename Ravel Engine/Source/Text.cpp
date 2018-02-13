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
	local = factory()->CreateComponent<Transform>();
	size = 10;
}

void Text::Render()
{
	Vector2 prev(0, 0);
	Vector2 position = local->position;
	for(char ch : _text){
		FontSystem::font f = GetFontManager()->FetchFont(font, ch);
		prev = Vector2(f.l, f.h);
		local->position.x += prev.x;
		Vector2 uv = Vector2((f.x / f.sz), (f.y / f.sy));
		Vector2 scale = Vector2((f.l/ f.sz), (f.h / f.sy));
		local->hscale = scale.x * size * 10;
		local->vscale = scale.y * size * 10;
		GetGraphicsManager()->Renderer()->Render(f.sampleid, local->GetLocalTransforms(), uv, scale, true, 1);
	}

	local->SetPosition(position);
}

void Text::SetFontSize(size_t size)
{
	this->size = size;
}
