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
	RegisterComponent<Canvas>("Canvas");
	RegisterComponent<AudioSource>("AudioSource");
	RegisterComponent<AudioMixer>("AudioMixer");
	RegisterComponent<NavMeshBoundVolume>("NavMeshBoundVolume");
	RegisterComponent<LinePrimitive>("LinePrimitive");
}

size_t Factory::LoadFromFile(std::string const&  file)
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

		m_Obj->Tag = gameobject["Tag"].GetString();

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

		json.close();

		return m_Obj->GetInstanceID();
	}
	else {
		std::cout << "GameObject failed to load  --> " << file << std::endl;
	}
	return -1;
}

Factory::pGameObject& Factory::CreateGameObject(std::string& name)
{
	
	pGameObject obj = std::make_unique<GameObject>();
	if (_refcount.count(name) == 1) {
		//name is a repeat
		size_t count = _refcount[name]++;
		name += ("_copy" + std::to_string(count));
	}
	else
		_refcount[name] = 1;
	obj->Instantiate(name);
	size_t id = obj->GetInstanceID();
	_go[id] = std::move(obj);
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

Factory::pGameObject& Factory::GetGameObject(size_t instanceID) {
	return _go[instanceID];
}

std::string const & Factory::ComponentTypeName(std::string const & tag)
{
	return _componentRegistry[HASH(tag)].second;
}

RavelBehaviour * Factory::CreateComponent(std::string const & tag)
{
	std::cout << "Creating Component " << tag << " from factory" << std::endl;
	RavelBehaviour* com = _component[HASH(_componentRegistry[HASH(tag)].second)]->Clone();
	std::cout << tag << " created" << std::endl;
	return com;
}
