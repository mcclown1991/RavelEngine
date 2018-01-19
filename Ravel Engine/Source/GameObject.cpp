#include "GameObject.h"

GameObject::GameObject() : RavelObject(), transform(
	Transform()), IsActive(true), m_Component_List()
{
	std::cout << "Gameobject created!" << std::endl;

	m_Functionptr["Update"] = &GameObject::Update;
	m_Functionptr["OnDestory"] = &GameObject::OnDestory;
	m_Functionptr["OnMouseDown"] = &GameObject::OnMouseDown;

	m_ColFunctionptr["OnCollisionEnter2D"] = &GameObject::OnCollisionEnter2D;
}

GameObject::~GameObject(){
	delete transform;
	for (auto iter : m_Component_List){
		delete iter.second->transform;
		delete iter.second;
	}
	m_Component_List.clear();
}

void GameObject::Update(){
	for (auto iter : m_Component_List) {
		iter.second->Update();
	}
}

void GameObject::OnDestory(){

	for (auto iter : m_Component_List){
		iter.second->OnDestory();
	}
}

void GameObject::OnMouseDown()
{
	for (auto iter : m_Component_List) {
		iter.second->OnMouseDown();
	}
}

void GameObject::OnCollisionEnter2D(Collider2D * other)
{
	for (auto iter : m_Component_List) {
		iter.second->OnCollisionEnter2D(other);
	}
}

bool GameObject::Draw()
{
	return true;
}

void GameObject::SetActive(bool isactive){
	IsActive = isactive;
	for (auto iter : m_Component_List){
		iter.second->enabled = IsActive;
	}
}

void GameObject::AddParent(Transform* trans)
{
	transform->parent = trans;
}

void GameObject::SendMessage(std::string const & functionName)
{
	(this->*m_Functionptr[functionName])();
}

void GameObject::SendMessage(std::string const & functionName, Collider2D * other)
{
	(this->*m_ColFunctionptr[functionName])(other);
}
