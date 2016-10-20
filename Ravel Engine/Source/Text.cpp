#include "Text.h"
#include "RavelEngine.h"

Text::Text() : text(), alignment(HGETEXT_LEFT), mode(Mode::SMALL), color(0xFF000000), _small(nullptr), _large(nullptr), _render(_small)
{
}

Text::~Text()
{
}

void Text::OnStart()
{
	_large = RavelEngine::GetRavelEngine()->GetFontLarge();
	_small = RavelEngine::GetRavelEngine()->GetFontSmall();
	_render = _large;
	GetGFX()->AddText(this);
}

void Text::Update()
{
}

void Text::OnDestory()
{
}

void Text::Render()
{
	_render->SetColor(color);
	_render->Render(parent->position.x + transform->position.x, parent->position.y + transform->position.y, alignment, text.c_str());
}
