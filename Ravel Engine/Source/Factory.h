#ifndef FACTORY_H
#define FACTORY_H

#include <map>
#include <functional>
#include <memory>
#include <unordered_map>
#include "System.h"
#include "GameObject.h"
#include "GraphicsManager.h"


#undef SendMessage
class Factory : public System
{
private:
	
	typedef GameObject goc;
	std::map<size_t, std::unique_ptr<GameObject> > _go;
	std::unordered_map<size_t, Component*> _component;

public:

	typedef std::unique_ptr<GameObject> pGOC;

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
	}
	void LoadFromFile(const std::string&);
	pGOC& CreateGameObject(const std::string&);
	void CreateEmptyObject();
	pGOC& GetGameObject(const std::string&);

	Component* CreateComponent(std::string const& name);

	template <typename T>
	void RegisterComponent();
};

Factory* factory();

inline size_t HASH(const std::string& hash) { return std::hash<std::string>()(hash);} 

#endif

template<typename T>
void Factory::RegisterComponent()
{
	_component[HASH(typeid(T).name())] = new T();
}
