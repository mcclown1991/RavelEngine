#pragma once
#include "BTNode.h"
#include "ScriptManager.h"

class BTMoveToTask : public BTTask {
public :
	BTMoveToTask();
	~BTMoveToTask();
	virtual BTMoveToTask* Clone() {
		return Memory()->alloc<BTMoveToTask>();
	}
	void SetBlackboardKey(std::string_view keyName);

	bool Execute() override;

private:
	std::string_view key;
};

