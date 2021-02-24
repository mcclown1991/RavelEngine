#include "AIController.h"
#include "Input.h"
#include "GameObject.h"

AIController::AIController() {

}

AIController::~AIController() {

}

void AIController::OnDestory() {

}

void AIController::Start() {
	Controller::Start();
	auto* component = pawn->GetComponent<BehaviourTree>();
	if (component)
		behaviour = component;
}

void AIController::LoadFromFile(std::string const& file) {
	// do standard loading of component
	std::ifstream json;
	json.open(file);
	rapidjson::IStreamWrapper isw(json);
	rapidjson::Document doc;
	doc.ParseStream(isw);

	if (doc.IsObject()) {
		rapidjson::Value& pc = doc["AIController"];

		IsActive = pc["IsActive"].GetBool();

		movement_speed = pc["Movement Speed"].GetFloat();
	}

	json.close();
}

void AIController::Update() {
	while (!moveRequest.empty()) {
		Vector2 request = moveRequest.front();
		moveRequest.pop();
		if (request.Length() != 1)
			request.Normalize();
		pawn->SetPosition(pawn->position + request * movement_speed);
	}
}

void AIController::AttachBehaviourTree(BehaviourTree* tree) {
	behaviour = tree;
}

void AIController::PushMoveRequest(Vector2 direction) {
	moveRequest.push(direction);
}