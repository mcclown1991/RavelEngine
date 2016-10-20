#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <string>
#include <algorithm>
#include <map>
#include <typeinfo.h>
#include "RavelObject.h"
#include "Transform.h"
#include "Sprite2D.h"

class GameObject : public RavelObject
{
public:
	GameObject();
	virtual ~GameObject();

	void virtual OnStart();
	void virtual Update();
	void virtual OnDestory();

	void virtual OnMouseDown();

	bool Draw();

	void SetActive(bool isactive);

	void AddParent(Transform* trans);

	template <class T>
	T* AddComponent();

	template <typename T>
	std::multimap<std::string, Component* >::const_iterator GetComponent();

	Transform* transform;
	bool IsActive;
	std::string name;

private:
	struct COMPARATOR {
		bool operator()(Component const& l, Component const& r) {
			return l.CompID < r.CompID;
		}
	};

	std::multimap<std::string, Component* > m_Component_List;
};


template <class T>
T* GameObject::AddComponent()
{
	T* newComp = new T();
	m_Component_List.insert(std::pair<std::string, Component*>(typeid(T).name(), newComp));
	//m_Component_List[typeid(T).name()] = newComp;
	newComp->gameObject = this;
	newComp->parent = transform;
	newComp->transform = new Transform();
	newComp->OnStart();
	return newComp;
}

template <typename T>
std::multimap<std::string, Component* >::const_iterator GameObject::GetComponent()
{
	std::string identifier = typeid(T).name();
	//return dynamic_cast<T*>(m_Component_List[identifier]);
	return m_Component_List.find(identifier);
}

#endif