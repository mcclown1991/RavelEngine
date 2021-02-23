#include "PrintTask.h"

#include <iostream>
#include "BehaviourTree.h"

BTPrintTask::BTPrintTask() : BTTask() {
}

BTPrintTask::~BTPrintTask() {
	
}

bool BTPrintTask::Execute() {
	parent->ExecuteTask(nodeName);
	return true;
}
