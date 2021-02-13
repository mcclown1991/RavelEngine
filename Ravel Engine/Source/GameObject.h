#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <string>
#include <algorithm>
#include <map>
#include <typeinfo>
#include <string>
#include <string_view>
#include "RavelObject.h"
#include "Transform.h"
#include "Sprite2D.h"
#include "Collider2D.h"
#include "MemoryManager.h"

#undef SendMessage
class Factory;
class GameObject : public RavelObject
{
public:
	GameObject();
	virtual ~GameObject();

	virtual GameObject* Clone() { return nullptr; }

	bool Draw();

	void SetActive(bool isactive);

	void AddParent(Transform* trans);

	typedef std::pair<std::multimap<std::string, RavelBehaviour* >::iterator, std::multimap<std::string, RavelBehaviour* >::iterator> ComponentList;

	template <class T>
	T* AddComponent();

	Component* AddComponent(std::string const& tag);

	template <typename T>
	T* GetComponent();
	
	template <typename T>
	ComponentList GetComponents();

	template <typename T>
	T* GetComponentWithTag(std::string const& tag);

	// Reflection for internal use only, it will not work on public use
	void SendMessage(std::string const& functionName);
	void SendMessage(std::string const& functionName, Collider2D* other);

	Transform* transform;
	bool IsActive;
	std::string Tag;

private:
	struct COMPARATOR {
		bool operator()(Component const& l, Component const& r) {
			return l.CompID < r.CompID;
		}
	};

	std::multimap<std::string, RavelBehaviour* > m_Component_List;

	std::map<std::string_view, void (GameObject::*)()> m_Functionptr;
	std::map<std::string_view, void (GameObject::*)(Collider2D*)> m_ColFunctionptr;

	// private functions for updating
	void Start();
	void Update();
	void OnDestory();
	void OnMouseDown();

	void OnCollisionEnter2D(Collider2D* other);
	void OnCollisionStay2D(Collider2D* other);
	void OnCollisionExit2D(Collider2D* other);
};

#include "Factory.h"

template <class T>
T* GameObject::AddComponent()
{
	T* newComp = factory()->CreateComponent<T>();
	//T* newComp = new T();
	m_Component_List.insert(std::pair<std::string, RavelBehaviour*>(typeid(T).name(), newComp));
	newComp->gameObject = this;
	newComp->transform = Memory()->alloc<Transform>();
	newComp->transform->parent = transform;
	newComp->OnEnable();
	return newComp;
}

template <typename T>
T* GameObject::GetComponent()
{
	std::string identifier = typeid(T).name();
	std::multimap<std::string, RavelBehaviour* >::const_iterator iter = m_Component_List.find(identifier);
	if (iter == m_Component_List.end())
		return nullptr;
	return dynamic_cast<T*>(iter->second);
}

template <typename T>
GameObject::ComponentList GameObject::GetComponents() {
	std::string identifier = typeid(T).name;
	return m_Component_List.equal_range(identifier);
}

template <typename T>
T* GameObject::GetComponentWithTag(std::string const& tag) {
	for (auto& it : m_Component_List) {
		if (it.second->tag == tag)
			return dynamic_cast<T*>(it.second);
	}
}

#endif