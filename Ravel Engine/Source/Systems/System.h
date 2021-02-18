#ifndef SYSTEM_H
#define SYSTEM_H

class System
{
public:
	System(){};
	virtual ~System() {};
	virtual void Init() = 0;
	virtual void Update() = 0;
	//messaging
};
#endif