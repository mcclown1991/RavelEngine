#include "Script.h"

Script::Script() : RavelBehaviour(), m_Filename(std::string()), m_OwnerID(0) {

}

Script::~Script() {

}

void Script::LoadFromFile(std::string const& file) {
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

		std::size_t pos = path.find(".");
		m_Filename = path.substr(0, pos);

		LoadScript(RavelEngine::getGameDataPath().data() + path);
	}

	json.close();
}

void Script::Update() {
	if(!m_Filename.empty())
		GetScriptManager()->UpdateScript(m_Filename, "Update", m_OwnerID, GetTime()->deltaTime);
}

void Script::OnDestory() {
	CallEvent("OnDestroy", 0);
	this->~Script();
}

void Script::LoadScript(std::string const& filename) {
	GetScriptManager()->LoadScript(filename);

	std::cout << "Attaching script: " << m_Filename << std::endl;

	m_OwnerID = gameObject->GetInstanceID();
	std::cout << "Owner's ID: " << m_OwnerID << std::endl;
	GetScriptManager()->UpdateScript(m_Filename, "OnStart", m_OwnerID, 0);
}