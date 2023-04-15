#ifndef FACTORY_H
#define FACTORY_H

#include <map>
#include <functional>
#include <memory>
#include <unordered_map>
#include "System.h"
#include "GraphicsManager.h"
#include "GameObject.h"
#include "BTNode.h"

#undef SendMessage
class Factory : public System
{
private:
	
	typedef GameObject goc;
	std::map<size_t, std::unique_ptr<GameObject> > _go;
	std::unordered_map<size_t, RavelBehaviour*> _component;
	std::unordered_map<size_t, std::pair<size_t, std::string>> _componentRegistry;
	std::map<std::string, size_t> _refcount;

	std::unordered_map<size_t, BTNode*> _btNode;
	std::unordered_map<size_t, std::pair<size_t, std::string>> _btNodeRegistry;

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

		for (auto& iter : _component) {
			iter.second->OnDestory();
			Memory()->dealloc(iter.second);
		}
		_component.clear();
		_componentRegistry.clear();

		for (auto& iter : _btNode) {
			iter.second->~BTNode();
			Memory()->dealloc(iter.second);
		}
		_btNode.clear();
		_btNodeRegistry.clear();
	}
	virtual void RemoveGameObject(size_t id) {
		_go.erase(id);
	}
	size_t LoadFromFile(std::string const&);
	pGameObject& CreateGameObject(std::string_view);
	void CreateEmptyObject();
	pGameObject& GetGameObject(const std::string&);
	pGameObject& GetGameObject(size_t instanceID);

	std::string const& ComponentTypeName(std::string const& tag);

	RavelBehaviour* CreateComponent(std::string const& name);

	BTNode* CreateBTNode(std::string const& name);
	
	template <typename T>
	T* CreateComponent();

	template <typename T>
	T* CreateBTNode();

	template <typename T>
	constexpr void RegisterComponent(std::string const& tag);

	template <typename T>
	constexpr void RegisterBTNode(std::string const& tag);
};

Factory* factory();

inline size_t HASH(const std::string& hash) { return std::hash<std::string>()(hash);} 

template<typename T>
T * Factory::CreateComponent()
{
	return dynamic_cast<T*>(_component[HASH(typeid(T).name())]->Clone());
}

template <typename T>
T* Factory::CreateBTNode() {
	return dynamic_cast<T*>(_btNode[HASH(typeid(T).name())]->Clone());
}


template<typename T>
constexpr void Factory::RegisterComponent(std::string const& tag)
{
	size_t hash = HASH(tag);

	// given a tag -> hashcode, typename
	_componentRegistry[hash] = std::pair<size_t, std::string>(hash, typeid(T).name());

	// given typename -> maps to component
	_component[HASH(_componentRegistry[hash].second)] = Memory()->alloc<T>();
}

template <typename T>
constexpr void Factory::RegisterBTNode(std::string const& tag) {
	size_t hash = HASH(tag);

	_btNodeRegistry[hash] = std::pair(hash, typeid(T).name());

	_btNode[HASH(_btNodeRegistry[hash].second)] = Memory()->alloc<T>();
}

#endif