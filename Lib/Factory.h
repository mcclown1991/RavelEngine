#ifndef FACTORY_H
#define FACTORY_H

#include <map>
#include <functional>
#include <memory>
#include "System.h"
#include "GameObject.h"
#include "GraphicsManager.h"

//serial reader
class Factory : public System
{
private:
	
	typedef GameObject goc;
	std::map<size_t, std::unique_ptr<GameObject> > _go;

public:

	typedef std::unique_ptr<GameObject> pGOC;

	Factory();
	virtual ~Factory();
	virtual void Init() {}
	virtual void Update() {
		for (auto& iter : _go){
			iter.second->Update();
		}
	}
	void Quit(){
		for (auto& iter : _go){
			iter.second->OnDestory();
		}
	}
	void LoadFromFile(const std::string&);
	pGOC& CreateGameObject(const std::string&);
	void CreateEmptyObject();
	pGOC& GetGameObject(const std::string&);

	//template <typename T>
	//std::unique_ptr<T>& CreateComponent();
};

Factory* factory();

inline size_t HASH(const std::string& hash) { return std::hash<std::string>()(hash);} 

#endif