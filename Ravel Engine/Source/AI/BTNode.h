#pragma once

#include <vector>
#include <string>

class BehaviourTree;

class BTNode {
public:
	BTNode(std::string name) : name(name) {};
	~BTNode() {};

	virtual bool Execute() {
		return next->Execute();
	};

protected:
	BehaviourTree* parent;
	std::string name;

private:
	BTNode * next;
};

class BTDecorator : public BTNode {
public:
	BTDecorator(std::string name);
	~BTDecorator() {};

	virtual bool Execute() = 0;
};

class BTServices : public BTNode {
public:
	BTServices(std::string name);
	~BTServices() {};

	virtual bool Execute() = 0;
};

class BTComposite : public BTNode {
public:
	BTComposite(std::string name);
	~BTComposite() {};

	virtual bool Execute() = 0;
	virtual void AddChildNode(BTComposite* child);
	virtual void AddDecorator(BTDecorator* decorator);
	virtual void AddService(BTServices* service);

protected:
	std::vector<BTComposite*> children;
	std::vector<BTDecorator*> conditions;
	std::vector<BTServices*> services;
};

class BTTask : public BTComposite {
public:
	BTTask(std::string name);
	~BTTask() {};

	virtual bool Execute() = 0;
};

class BTSelector : public BTComposite {
public:
	BTSelector(std::string name);
	~BTSelector();

	virtual bool Execute();
};

class BTSequence : public BTComposite {
public:
	BTSequence(std::string name);
	~BTSequence();

	virtual bool Execute();
};