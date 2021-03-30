#include "PlayerController.h"
#include "Input.h"
#include "GameObject.h"

PlayerController::PlayerController() {

}

PlayerController::~PlayerController() {

}

void PlayerController::OnDestory() {
	this->~PlayerController();
}

void PlayerController::Start() {
	Controller::Start();
}

void PlayerController::LoadFromFile(std::string const& file) {
	// do standard loading of component
	std::ifstream json;
	json.open(file);
	rapidjson::IStreamWrapper isw(json);
	rapidjson::Document doc;
	doc.ParseStream(isw);

	if (doc.IsObject()) {
		rapidjson::Value& pc = doc["PlayerController"];

		IsActive = pc["IsActive"].GetBool();

		movement_speed = pc["Movement Speed"].GetFloat();
	}

	json.close();
}

void PlayerController::Update() {
	// trap keys
	float delta = Input::GetAxis("Horizontal") * movement_speed;
	pawn->SetPosition(pawn->position + pawn->right * delta);
	delta = Input::GetAxis("Vertical") * movement_speed;
	pawn->SetPosition(pawn->position + pawn->up * delta);
}