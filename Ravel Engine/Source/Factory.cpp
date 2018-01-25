#include "Factory.h"
#include "BoxCollider.h"
#include "Sprite2D.h"
#include <typeinfo.h>

Factory* factory()
{
	static Factory s;
	return(&s);
}

Factory::Factory()
{
}

Factory::~Factory()
{
}

void Factory::Init() {
	RegisterComponent<Transform>();
	RegisterComponent<BoxCollider>();
	RegisterComponent<Sprite2D>();
}

void Factory::LoadFromFile(const std::string& file)
{ 
}

Factory::pGOC& Factory::CreateGameObject(const std::string& name)
{
	int id = HASH(name);
	//_go[id] = std::unique_ptr<GameObject>();
	_go[id] = std::make_unique<GameObject>();
	_go[id]->name = name;
	return _go[id];
}

void Factory::CreateEmptyObject()
{
	std::string _empty("empty");
	_go[HASH(_empty)] = std::make_unique<GameObject>();
}

Factory::pGOC& Factory::GetGameObject(const std::string& name)
{
	size_t h = HASH(name);
	return _go[h];
}

Component * Factory::CreateComponent(std::string const & name)
{
	Component* com = _component[HASH(name)]->Clone();
	return com;
}
