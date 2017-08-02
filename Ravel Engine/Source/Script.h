#ifndef SCRIPT_H
#define SCRIPT_H

#include "Component.h"
#include "ScriptManager.h"

class Script : public Component {
public:
	Script();
	virtual ~Script();

	virtual void OnStart();
	virtual void Update();
	virtual void OnDestory();
};

#endif