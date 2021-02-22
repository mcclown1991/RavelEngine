#pragma once

#include <string>

#include "BTNode.h"

class BTPrintTask : public BTTask {
public:
	BTPrintTask();
	virtual ~BTPrintTask();

	virtual BTPrintTask* Clone() {
		return Memory()->alloc<BTPrintTask>();
	}

	virtual bool Execute() override;
};

