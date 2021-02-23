#pragma once
#include "types.h"

#include <map>
#include <string>
#include <string_view>
#include <optional>
#include "MemoryManager.h"

class Blackboard {
public:
	Blackboard() {};
	~Blackboard();

	// getter
	bool GetValueAsBool(std::string_view keyName);
	int GetValueAsInt(std::string_view keyName);
	float GetValueAsFloat(std::string_view keyName);
	double GetValueAsDouble(std::string_view keyName);
	std::string GetValueAsString(std::string_view keyName);

	template<class DataType>
	DataType GetValue(std::string_view keyName);

	template<class UserObject>
	std::optional<UserObject> GetValueAsObject(std::string_view keyName);

	// setter
	void SetValueAsBool(std::string_view keyName, bool value);
	void SetValueAsInt(std::string_view keyName, int value);
	void SetValueAsFloat(std::string_view keyName, float value);
	void SetValueAsDouble(std::string_view keyName, double value);
	void SetValueAsString(std::string_view keyName, std::string_view value);

	template<class DataType>
	void SetValue(std::string_view keyName, DataType value);
	
	template<class UserObject>
	void SetValueAsObject(std::string_view keyName, UserObject* value);

private:
	std::map<std::string, BaseObject*> m_Keys;
};

template<class UserObject>
std::optional<UserObject> Blackboard::GetValueAsObject(std::string_view keyName) {
	if (!m_Keys.count(keyName.data()))
		return std::optional<UserObject>();
	auto* object = dynamic_cast<Object<UserObject>*>(m_Keys[keyName]);
	if(object)
		return std::optional<UserObject>(object->data());
	return std::optional<UserObject>();
}

template <class UserObject>
void Blackboard::SetValueAsObject(std::string_view keyName, UserObject* value) {
	auto* data = Memory()->alloc<Object<UserObject>>();
	data->set(value);
	m_Keys[keyName.data()] = data;
}

template<class DataType>
void Blackboard::SetValue(std::string_view keyName, DataType value) {
	auto* data = Memory()->alloc<Object<DataType>>();
	data->set(value);
	m_Keys[keyName.data()] = data;
}

template<class DataType>
DataType Blackboard::GetValue(std::string_view keyName) {
	if (!m_Keys.count(keyName.data()))
		return nullptr;
	auto* object = dynamic_cast<Object<DataType>*>(m_Keys[keyName]);
	if (object)
		return object->data();
	return nullptr;
}