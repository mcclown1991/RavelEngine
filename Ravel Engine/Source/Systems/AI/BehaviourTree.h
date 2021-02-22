#pragma once
#include "BTNode.h"
#include "Blackboard.h"
#include "Behaviour/RavelBehaviour.h"
#include "RavelEngine.h"

class Script;

class BehaviourTree : public RavelBehaviour{
public:
	BehaviourTree();
	~BehaviourTree();

	BehaviourTree* Clone() {
		return Memory()->alloc<BehaviourTree>();
	}

	void OnDestory();

	void AddConnection(BTComposite* composite);
	void AddBlackBoard(Blackboard* blackboard);
	void LoadFromFile(std::string const& file);

	bool ExecuteTask(std::string_view task);

	Blackboard* GetBlackboard() const {
		return blackboard;
	}

private:
	BTNode * root;
	Blackboard* blackboard;
	Script* definitions;
	
	void LoadFromFile(BTComposite* parent, rapidjson::Value const& json);
	void InitScriptFunctions();
};
