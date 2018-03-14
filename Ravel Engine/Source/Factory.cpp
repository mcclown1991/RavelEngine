#include "Factory.h"
#include "ComponentHeader.h"
#include "rapidjson/document.h"
#include <rapidjson\istreamwrapper.h>
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
	RegisterComponent<Transform>("Transform");
	RegisterComponent<RectTransform>("RectTransform");
	RegisterComponent<BoxCollider>("BoxCollider");
	RegisterComponent<Sprite2D>("Sprite2D");
	RegisterComponent<Text>("Text");
	RegisterComponent<Script>("Script");
}

void Factory::LoadFromFile(const std::string& file)
{
	std::ifstream json;
	json.open(file);
	rapidjson::IStreamWrapper isw(json);
	rapidjson::Document doc;
	doc.ParseStream(isw);

	if (doc.IsObject()) {
		
		rapidjson::Value& gameobject = doc["GameObject"];

		std::string name = gameobject["name"].GetString();
		pGameObject& m_Obj = CreateGameObject(name);

		m_Obj->IsActive = gameobject["IsActive"].GetBool();

		Vector2 pos;
		pos.x = gameobject["Transform"]["X"].GetFloat();
		pos.y = gameobject["Transform"]["Y"].GetFloat();

		m_Obj->transform->position = pos;

		// components
		rapidjson::SizeType size = gameobject["Components"].MemberCount();
		for (rapidjson::Value::ConstMemberIterator it = gameobject["Components"].MemberBegin(); it != gameobject["Components"].MemberEnd(); ++it) {
			Component* comp = m_Obj->AddComponent(it->value["typename"].GetString());
			comp->LoadFromFile(it->value["metafile"].GetString());
		}
	}

	//// start reading serialized data
	//std::ifstream data;
	//data.open(file + ".raveldata");

	//if (data.is_open()) {
	//	std::string line;
	//	// data file layout
	//	// start with gameobject
	//	std::string::iterator iter;
	//	std::getline(data, line);
	//	// create gameobject
	//	pGameObject& m_Obj = CreateGameObject(line);

	//	// gameobject's transform information


	//	// next is component count
	//	std::getline(data, line);
	//	int count;
	//	count = std::stoi(line);

	//	for (int i = 0; i < count; ++i) {
	//		// create components
	//		std::getline(data, line);
	//		//find <inside>
	//		std::string comp = line.substr(1, line.size() - 2);
	//		Component* component = m_Obj->AddComponent(comp);
	//	}
	//}
}

Factory::pGameObject& Factory::CreateGameObject(const std::string& name)
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

Factory::pGameObject& Factory::GetGameObject(const std::string& name)
{
	size_t h = HASH(name);
	return _go[h];
}

std::string const & Factory::ComponentTypeName(std::string const & tag)
{
	return _componentRegistry[HASH(tag)].second;
}

RavelBehaviour * Factory::CreateComponent(std::string const & tag)
{
	RavelBehaviour* com = _component[HASH(_componentRegistry[HASH(tag)].second)]->Clone();
	return com;
}
