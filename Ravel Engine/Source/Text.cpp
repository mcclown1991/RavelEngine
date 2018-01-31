#include "Text.h"
#include "RavelEngine.h"

Text::Text() : text(), alignment(0), mode(Mode::SMALL)//, color(0xFF000000)
{
}

Text::~Text()
{
}

void Text::Start()
{
	//_large = RavelEngine::GetRavelEngine()->GetFontLarge();
	//_small = RavelEngine::GetRavelEngine()->GetFontSmall();
	//_render = _large;
	GetGraphicsManager()->AddText(this);
}

void Text::Render()
{
	//_render->SetColor(color);
	//_render->Render(parent->position.x + transform->position.x, parent->position.y + transform->position.y, alignment, text.c_str());
}
