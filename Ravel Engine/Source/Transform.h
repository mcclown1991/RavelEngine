#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "Component.h"

class Transform : public Component{
public:
	Transform();
	virtual ~Transform();

	virtual void OnStart();
	virtual void Update();
	virtual void OnDestory();

	void SetPosition(fVector2);

	fVector2 GetPosition();

	fVector2 position;
};

#endif