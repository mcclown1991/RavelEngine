#pragma once
#include "Controller.h"
#include "BehaviourTree.h"
#include <queue>

class AIController : public Controller {
public:
	AIController();
	virtual ~AIController();
	virtual AIController* Clone() {
		return Memory()->alloc<AIController>();
	}

	virtual void LoadFromFile(std::string const& file);

	virtual void OnDestory();
	virtual void Start();
	virtual void Update();

	void AttachBehaviourTree(BehaviourTree* tree);
	void PushMoveRequest(Vector2 direction);

private:
	BehaviourTree* behaviour;
	std::queue<Vector2> moveRequest;
};

