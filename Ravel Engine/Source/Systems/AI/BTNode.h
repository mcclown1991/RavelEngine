#pragma once

#include <vector>
#include <string>

#include "MemoryManager.h"

class BehaviourTree;

class BTNode {
public:
	BTNode() : name(std::string()) {};
	~BTNode() {};

	virtual BTNode* Clone() {
		return Memory()->alloc<BTNode>();
	}

	virtual bool Execute() {
		return next->Execute();
	};

	virtual void SetNodeName(std::string_view name) {
		this->name = name.data();
	}

	virtual void SetParent(BehaviourTree* node) {
		parent = node;
	}

protected:
	BehaviourTree* parent;
	std::string name;

private:
	BTNode * next;
};

class BTDecorator : public BTNode {
public:
	BTDecorator();
	~BTDecorator() {};

	virtual bool Execute() = 0;
};

class BTServices : public BTNode {
public:
	BTServices();
	~BTServices() {};

	virtual bool Execute() = 0;
};

class BTComposite : public BTNode {
public:
	BTComposite();
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
	BTTask();
	~BTTask() {};

	virtual bool Execute() = 0;
};

class BTSelector : public BTComposite {
public:
	BTSelector();
	~BTSelector();

	virtual BTSelector* Clone() {
		return Memory()->alloc<BTSelector>();
	}

	virtual bool Execute();
};

class BTSequence : public BTComposite {
public:
	BTSequence();
	~BTSequence();

	virtual BTSequence* Clone() {
		return Memory()->alloc<BTSequence>();
	}

	virtual bool Execute();
};