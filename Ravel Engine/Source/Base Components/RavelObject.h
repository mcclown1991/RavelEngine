#ifndef RAVELOBJECT_H
#define RAVELOBJECT_H

#include <string>
#include <string_view>
#include <functional>
#include "DataType.h"
#include "MemoryManager.h"

class RavelObject{
public:
	RavelObject() : Hash(std::hash<std::string_view>()), instanceID(0) {};
	virtual ~RavelObject() {};

	virtual std::size_t GetInstanceID() {
		return instanceID;
	}

	virtual RavelObject* Clone() = 0;

	virtual void Instantiate(std::string const& name) {
		this->name = name;
		instanceID = Hash(name);
	}

	std::string name;

private:
	std::hash<std::string_view> Hash;
	size_t instanceID;

};

#endif
