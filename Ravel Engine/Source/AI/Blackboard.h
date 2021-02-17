#pragma once
#include "../types.h"

#include <map>
#include <string>
#include <string_view>
#include "../MemoryManager.h"

class Blackboard {
public:
	Blackboard() {};
	~Blackboard() {};

	// getter
	bool GetValueAsBool(std::string_view keyName);
	int GetValueAsInt(std::string_view keyName);
	float GetValueAsFloat(std::string_view keyName);
	double GetValueAsDouble(std::string_view keyName);
	std::string GetValueAsString(std::string_view keyName);

	template<class DataType>
	DataType GetValue(std::string_view keyName);

	template<class UserObject>
	UserObject GetValueAsObject(std::string_view keyName);

	// setter
	void SetValueAsBool(std::string_view keyName, bool value);
	void SetValueAsInt(std::string_view keyName, int value);
	void SetValueAsFloat(std::string_view keyName, float value);
	void SetValueAsDouble(std::string_view keyName, double value);

	template<class DataType>
	void SetValue(std::string_view keyName, DataType value);
	
	template<class UserObject>
	void SetValueAsObject(std::string_view keyName, UserObject* value);

private:
	std::map<std::string_view, BaseObject*> m_Keys;
};

template<class UserObject>
UserObject Blackboard::GetValueAsObject(std::string_view keyName) {
	auto* object = dynamic_cast<Object<UserObject>*>(m_Keys[keyID]);
	if(object)
		return object->data();
}

template <class UserObject>
void Blackboard::SetValueAsObject(std::string_view keyName, UserObject* value) {
	m_keys[keyName] = value;
}

template<class DataType>
void SetValue(std::string_view keyName, DataType value) {
	m_Keys[keyName] = Memory()->alloc<DataType>();
}