#ifndef RAVELOBJECT_H
#define RAVELOBJECT_H

#include <string>
#include <functional>
#include "DataType.h"

class RavelObject{
public:
	RavelObject() {};
	virtual ~RavelObject() {};

	virtual std::size_t GetInstanceID() {
		return instanceID(name);
	}

	std::string name;

private:
	std::hash<std::string> instanceID;

};

#endif
