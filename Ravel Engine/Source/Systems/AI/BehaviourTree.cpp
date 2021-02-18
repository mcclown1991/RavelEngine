#include "BehaviourTree.h"

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