#pragma once
#include "../types.h"

#include <map>
#include <string>

class Blackboard {
public:
	Blackboard() {};
	~Blackboard() {};

	// getter and setter
	bool GetBlackboardValueAsBool(std::string const& keyID);
	int GetBlackboardValueAsInt(std::string const& keyID);
	float GetBlackboardValueAsFloat(std::string const& keyID);
	double GetBlackboardValueAsDouble(std::string const& keyID);

	template<class UserObject>
	UserObject GetBlackboardValueAsObject(std::string const& keyID);

private:
	std::map<std::string, BaseObject*> m_Keys;
};

template<class UserObject>
UserObject Blackboard::GetBlackboardValueAsObject(std::string const& keyID) {
	return dynamic_cast<Object<UserObject>*>(m_Keys[keyID])->data();
}