#include "GameObject.h"

GameObject::GameObject() : RavelObject(), transform(Memory()->alloc<Transform>()), IsActive(true), m_Component_List()
{
	std::cout << "Gameobject created!" << std::endl;

	m_Functionptr["Update"] = &GameObject::Update;
	m_Functionptr["OnDestory"] = &GameObject::OnDestory;
	m_Functionptr["OnMouseDown"] = &GameObject::OnMouseDown;

	m_ColFunctionptr["OnCollisionEnter2D"] = &GameObject::OnCollisionEnter2D;
	m_ColFunctionptr["OnCollisionStay2D"] = &GameObject::OnCollisionStay2D;
	m_ColFunctionptr["OnCollisionExit2D"] = &GameObject::OnCollisionExit2D;
}

GameObject::~GameObject(){
	Memory()->dealloc(transform);
}

void GameObject::Update(){
	for (auto iter : m_Component_List) {
		iter.second->Update();
	}
}

void GameObject::OnDestory(){

	for (auto iter : m_Component_List){
		iter.second->OnDestory();
		Memory()->dealloc(iter.second);
	}
	m_Component_List.clear();
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

void GameObject::OnCollisionStay2D(Collider2D * other)
{
	for (auto iter : m_Component_List) {
		iter.second->OnCollisionStay2D(other);
	}
}

void GameObject::OnCollisionExit2D(Collider2D * other)
{
	for (auto iter : m_Component_List) {
		iter.second->OnCollisionExit2D(other);
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

Component * GameObject::AddComponent(std::string const & tag)
{
	Component* newComp = factory()->CreateComponent(tag);
	m_Component_List.insert(std::pair<std::string, RavelBehaviour*>(factory()->ComponentTypeName(tag), static_cast<RavelBehaviour*>(newComp)));
	newComp->gameObject = this;
	newComp->transform = Memory()->alloc<Transform>();
	newComp->transform->parent = transform;
	static_cast<RavelBehaviour*>(newComp)->Start();
	return newComp;
}

void GameObject::SendMessage(std::string const & functionName)
{
	(this->*m_Functionptr[functionName])();
}

void GameObject::SendMessage(std::string const & functionName, Collider2D * other)
{
	(this->*m_ColFunctionptr[functionName])(other);
}
