#include "BTNode.h"
#include "BehaviourTree.h"

void BTNode::AssignRunningNode() {
	parent->AssignRunningNode(this);
}

BTDecorator::BTDecorator() : BTNode() {
}

BTServices::BTServices() : BTNode() {
}

BTComposite::BTComposite() : BTNode() {
}

void BTComposite::AddChildNode(BTComposite * child) {
	children.push_back(child);
}

void BTComposite::AddDecorator(BTDecorator * decorator) {
	conditions.push_back(decorator);
}

void BTComposite::AddService(BTServices * service) {
	services.push_back(service);
}

BTTask::BTTask() : BTComposite() {
}

BTSelector::BTSelector() : BTComposite() {

}

BTSelector::~BTSelector()
{
}

bool BTSelector::Execute()
{
	AssignRunningNode();
	for (BTServices* service : services) {
		service->Execute();
	}
	for (BTDecorator* condition : conditions) {
		if (!condition->Execute())
			return false;
	}
	bool result{ true };
	for (BTComposite* child : children) {
		if (!child->Execute())
			result = false;
	}
	return result;
}

BTSequence::BTSequence() : BTComposite() {
}

BTSequence::~BTSequence()
{
}

bool BTSequence::Execute()
{
	AssignRunningNode();
	for (BTServices* service : services) {
		service->Execute();
	}
	for (BTDecorator* condition : conditions) {
		if (!condition->Execute())
			return false;
	}
	for (BTComposite* child : children) {
		if (!child->Execute())
			return false;
	}
	return true;
}
