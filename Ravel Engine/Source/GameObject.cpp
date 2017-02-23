#include "GameObject.h"

GameObject::GameObject() : RavelObject(), transform(new Transform()), IsActive(true), m_Component_List()
{
	std::cout << "Gameobject created!" << std::endl;
}

GameObject::~GameObject(){
	delete transform;
	for (auto iter : m_Component_List){
		delete iter.second->transform;
		delete iter.second;
	}
	m_Component_List.clear();
}

void GameObject::OnStart(){

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

void GameObject::OnCollisionEnter(BoxCollider * other)
{
	for (auto iter : m_Component_List) {
		iter.second->OnCollisionEnter(other);
	}
}

bool GameObject::Draw()
{
	return true;
}

void GameObject::SetActive(bool isactive){
	IsActive = isactive;
	for (auto iter : m_Component_List){
		iter.second->SetActive(IsActive);
	}
}

void GameObject::AddParent(Transform* trans)
{
	transform->parent = trans;
}
