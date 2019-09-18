#ifndef RAVELOBJECT_H
#define RAVELOBJECT_H

#include <string>
#include <functional>

class RavelObject{
public:
	RavelObject() {};
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
	std::hash<std::string> Hash;
	size_t instanceID;

};

#endif
