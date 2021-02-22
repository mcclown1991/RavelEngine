#include "BehaviourTree.h"
#include "Factory.h"
#include "Script.h"

BehaviourTree::BehaviourTree() {
}

BehaviourTree::~BehaviourTree() {
}

void BehaviourTree::AddConnection(BTComposite* composite) {
	root = composite;
}

void BehaviourTree::AddBlackBoard(Blackboard* blackboard) {
	this->blackboard = blackboard;
}

void BehaviourTree::LoadFromFile(std::string const& file) {
	std::ifstream json;
	json.open(file);
	rapidjson::IStreamWrapper isw(json);
	rapidjson::Document doc;
	doc.ParseStream(isw);

	if(doc.IsObject()) {
		rapidjson::Value& root = doc["Nodes"];
		IsActive = root["IsActive"].GetBool();

		rapidjson::Value& connections = root["Nodes"];
		auto head = dynamic_cast<BTComposite*>(factory()->CreateBTNode(connections["node"].GetString()));
		if (head) {
			head->SetNodeName(root["name"].GetString());
			head->SetParent(this);
			AddConnection(head);
			if (connections.HasMember("Connection") && connections["Connection"].IsArray()) {
				rapidjson::Value& arr = connections["Connection"];
				LoadFromFile(head, arr);
			}
		}
		
		auto* comp = gameObject->AddComponent("Script");
		comp->LoadFromFile(file);
		definitions = dynamic_cast<Script*>(comp);
	}

	root->Execute();
}

void BehaviourTree::LoadFromFile(BTComposite* parent, rapidjson::Value const& json) {
	for (rapidjson::Value::ConstValueIterator it = json.Begin(); it != json.End(); ++it) {
		const rapidjson::Value& obj = *it;
		auto* node = dynamic_cast<BTComposite*>(factory()->CreateBTNode(obj["node"].GetString()));
		parent->AddChildNode(node);
		node->SetNodeName(obj["name"].GetString());
		node->SetParent(this);
		if (obj.HasMember("Connection") && obj["Connection"].IsArray()) {
			rapidjson::Value const& arr = obj["Connection"];
			LoadFromFile(node, arr);
		}
	}
}


bool BehaviourTree::ExecuteTask(std::string_view task) {
	definitions->CallEvent(task.data(), GetTime()->deltaTime);
	return true;
}

void BehaviourTree::InitScriptFunctions() {
	GetScriptManager()->AddFunction("GetBlackboardValue", [](lua_State* L)->int {});
}
