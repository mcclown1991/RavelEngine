#pragma once
#include "BTNode.h"
#include "Blackboard.h"

class BehaviourTree {
public:
	BehaviourTree();
	~BehaviourTree();

	void AddConnection(BTComposite* composite);
	void AddBlackBoard(Blackboard* blackboard);

private:
	BTNode * root;
	Blackboard* blackboard;
};