#include "PlayerController.h"
#include "Input.h"
#include "GameObject.h"

PlayerController::PlayerController() {

}

PlayerController::~PlayerController() {

}

void PlayerController::OnDestory() {

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
	if (OnKeyHold(VK_LEFT)) {
		pawn->SetPosition(pawn->position + pawn->right * -movement_speed);
	}
	if (OnKeyHold(VK_RIGHT)) {
		pawn->SetPosition(pawn->position + pawn->right * movement_speed);
	}
	if (OnKeyHold(VK_UP)) {
		pawn->SetPosition(pawn->position + pawn->up * movement_speed);
	}
	if (OnKeyHold(VK_DOWN)) {
		pawn->SetPosition(pawn->position + pawn->up * -movement_speed);
	}
}