#include "Script.h"
#include "Time.h"

Script::Script() {

}

Script::~Script() {

}

void Script::Update() {
	GetScriptManager()->UpdateScript(m_Filename, "Update", m_OwnerID, 0);
}

void Script::Destory() {
	CallEvent("OnDestroy", 0);
}

void Script::LoadScript(std::string const& filename) {
	m_Filename = filename;

	GetScriptManager()->LoadScript(m_Filename);
	std::size_t pos = m_Filename.find(".");
	m_Filename = m_Filename.substr(0, pos);

	std::cout << "Attaching script: " << m_Filename << std::endl;

	m_OwnerID = gameObject->GetInstanceID();
	std::cout << "Owner's ID: " << m_OwnerID << std::endl;
	GetScriptManager()->UpdateScript(m_Filename, "OnStart", m_OwnerID, 0);
}