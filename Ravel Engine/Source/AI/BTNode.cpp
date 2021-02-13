#include "BTNode.h"

BTDecorator::BTDecorator(std::string name) : BTNode(name) {
}

BTServices::BTServices(std::string name) : BTNode(name) {
}

BTComposite::BTComposite(std::string name) : BTNode(name) {
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

BTTask::BTTask(std::string name) : BTComposite(name) {
}

BTSelector::BTSelector(std::string name) : BTComposite(name) {

}

BTSelector::~BTSelector()
{
}

bool BTSelector::Execute()
{
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

BTSequence::BTSequence(std::string name) : BTComposite(name) {
}

BTSequence::~BTSequence()
{
}

bool BTSequence::Execute()
{
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
