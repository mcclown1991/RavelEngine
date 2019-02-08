#ifndef FACTORY_H
#define FACTORY_H

#include <map>
#include <functional>
#include <memory>
#include <unordered_map>
#include "System.h"
#include "GraphicsManager.h"
#include "GameObject.h"

#undef SendMessage
class Factory : public System
{
private:
	
	typedef GameObject goc;
	std::map<size_t, std::unique_ptr<GameObject> > _go;
	std::unordered_map<size_t, RavelBehaviour*> _component;
	std::unordered_map<size_t, std::pair<size_t, std::string>> _componentRegistry;
	std::map<std::string, size_t> _refcount;

public:

	typedef std::unique_ptr<GameObject> pGameObject;

	Factory();
	virtual ~Factory();
	virtual void Init();
	virtual void Update() {
		for (auto& iter : _go){
			iter.second->SendMessage("Update");
		}
	}
	void Quit(){
		for (auto& iter : _go){
			iter.second->SendMessage("OnDestory");
		}
		_go.clear();
		_refcount.clear();
	}
	size_t LoadFromFile(std::string const&);
	pGameObject& CreateGameObject(std::string&);
	void CreateEmptyObject();
	pGameObject& GetGameObject(const std::string&);
	pGameObject& GetGameObject(size_t instanceID);

	std::string const& ComponentTypeName(std::string const& tag);

	RavelBehaviour* CreateComponent(std::string const& name);
	
	template <typename T>
	T* CreateComponent();

	template <typename T>
	void RegisterComponent(std::string const& tag);
};

Factory* factory();

inline size_t HASH(const std::string& hash) { return std::hash<std::string>()(hash);} 

template<typename T>
T * Factory::CreateComponent()
{
	return dynamic_cast<T*>(_component[HASH(typeid(T).name())]->Clone());
}

template<typename T>
void Factory::RegisterComponent(std::string const& tag)
{
	size_t hash = HASH(tag);

	// given a tag -> hashcode, typename
	_componentRegistry[hash] = std::pair<size_t, std::string>(hash, typeid(T).name());

	// given typename -> maps to component
	_component[HASH(_componentRegistry[hash].second)] = Memory()->alloc<T>();
}

#endif