#pragma once
#include "RavelBehaviour.h"

class Controller : public RavelBehaviour {
public:
	Controller();
	virtual ~Controller();
	virtual Controller* Clone() {
		return Memory()->alloc<Controller>();
	}

	virtual void OnDestory();
	virtual void Start();

	float GetMovementSpeed() const;
	void SetMovementSpeed(float speed);

protected:
	Transform* pawn;
	float movement_speed;
};
