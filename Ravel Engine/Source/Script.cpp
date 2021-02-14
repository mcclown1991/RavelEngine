#include "Script.h"

Script::Script() : RavelBehaviour(), m_Filename(std::string_view()), m_OwnerID(0) {

}

Script::~Script() {

}

void Script::LoadFromFile(std::string const & file) {
	// do standard loading of component
	std::ifstream json;
	json.open(file);
	rapidjson::IStreamWrapper isw(json);
	rapidjson::Document doc;
	doc.ParseStream(isw);

	if (doc.IsObject()) {
		rapidjson::Value& root = doc["Script"];

		IsActive = root["IsActive"].GetBool();

		std::string path = root["Script path"].GetString();

		LoadScript(path);
	}

	json.close();
}

void Script::Update() {
	GetScriptManager()->UpdateScript(m_Filename.data(), "Update", m_OwnerID, 0);
}

void Script::OnDestory() {
	CallEvent("OnDestroy", 0);
	this->~Script();
}

void Script::LoadScript(std::string const& filename) {
	m_Filename = filename;

	GetScriptManager()->LoadScript(m_Filename.data());
	std::size_t pos = m_Filename.find(".");
	m_Filename = m_Filename.substr(0, pos);

	std::cout << "Attaching script: " << m_Filename << std::endl;

	m_OwnerID = gameObject->GetInstanceID();
	std::cout << "Owner's ID: " << m_OwnerID << std::endl;
	GetScriptManager()->UpdateScript(m_Filename.data(), "OnStart", m_OwnerID, 0);
}