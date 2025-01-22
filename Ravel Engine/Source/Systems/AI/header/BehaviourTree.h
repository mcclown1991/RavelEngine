#pragma once
#include "BTNode.h"
#include "Blackboard.h"
#include "RavelBehaviour.h"
#include "RavelEngine.h"
#include "AIController.h"

class Script;

class BehaviourTree : public RavelBehaviour{
public:
	BehaviourTree();
	~BehaviourTree();

	BehaviourTree* Clone() {
		return Memory()->alloc<BehaviourTree>();
	}

	void Update() override {
		if(root)
			root->Execute();
	}
	void OnDestory();

	void AddConnection(BTComposite* composite);
	void AddBlackBoard(Blackboard* blackboard);
	void LoadFromFile(std::string const& file);

	bool ExecuteTask(std::string_view task);

	void AssignRunningNode(BTNode* node);
	BTNode* GetRunningNode() const;

	Blackboard* GetBlackboard() const {
		return blackboard;
	}

private:
	BTNode * root;
	Blackboard* blackboard;
	Script* definitions;
	std::vector<BTNode*> nodes;
	BTNode* runningNode;
	
	void LoadFromFile(BTComposite* parent, rapidjson::Value const& json);
	void InitScriptFunctions();
};
