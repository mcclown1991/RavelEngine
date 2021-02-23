#pragma once
#include "Controller.h"
class PlayerController : public Controller {
public:
	PlayerController();
	virtual ~PlayerController();
	virtual PlayerController* Clone() {
		return Memory()->alloc<PlayerController>();
	}

	virtual void LoadFromFile(std::string const& file);

	virtual void OnDestory();
	virtual void Start();
	virtual void Update();
};

