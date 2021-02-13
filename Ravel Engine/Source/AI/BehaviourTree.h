#pragma once
#include "BTNode.h"
#include "Blackboard.h"

class BehaviourTree {
public:
	BehaviourTree();
	~BehaviourTree();

	void AddConnection(BTComposite* composite);

private:
	BTNode * root;
	Blackboard* blackboard;
};