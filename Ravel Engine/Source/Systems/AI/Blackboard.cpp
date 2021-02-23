#include "Blackboard.h"

bool Blackboard::GetValueAsBool(std::string_view keyName) {
	if (!m_Keys.count(keyName.data()))
		return bool();
	auto* object = dynamic_cast<Object<bool>*>(m_Keys[keyName.data()]);
	if (object)
		return object->data();
	return bool();
}

int Blackboard::GetValueAsInt(std::string_view keyName) {
	if (!m_Keys.count(keyName.data()))
		return int();
	auto* object = dynamic_cast<Object<int>*>(m_Keys[keyName.data()]);
	if (object)
		return object->data();
	return int();
}

float Blackboard::GetValueAsFloat(std::string_view keyName) {
	if (!m_Keys.count(keyName.data()))
		return float();
	auto* object = dynamic_cast<Object<float>*>(m_Keys[keyName.data()]);
	if (object)
		return object->data();
	return float();
}

double Blackboard::GetValueAsDouble(std::string_view keyName) {
	if (!m_Keys.count(keyName.data()))
		return double();
	auto* object = dynamic_cast<Object<double>*>(m_Keys[keyName.data()]);
	if (object)
		return object->data();
	return double();
}

std::string Blackboard::GetValueAsString(std::string_view keyName) {
	if (!m_Keys.count(keyName.data()))
		return std::string();
	auto* object = dynamic_cast<Object<std::string>*>(m_Keys[keyName.data()]);
	if (object)
		return object->data();
	return std::string();
}

void Blackboard::SetValueAsBool(std::string_view keyName, bool value) {
	auto* data = Memory()->alloc<Object<bool>>();
	data->set(value);
	m_Keys[keyName.data()] = data;
}

void Blackboard::SetValueAsInt(std::string_view keyName, int value) {
	auto* data = Memory()->alloc<Object<int>>();
	data->set(value);
	m_Keys[keyName.data()] = data;
}

void Blackboard::SetValueAsFloat(std::string_view keyName, float value) {
	auto* data = Memory()->alloc<Object<float>>();
	data->set(value);
	m_Keys[keyName.data()] = data;
}

void Blackboard::SetValueAsDouble(std::string_view keyName, double value) {
	auto* data = Memory()->alloc<Object<double>>();
	data->set(value);
	m_Keys[keyName.data()] = data;
}

void Blackboard::SetValueAsString(std::string_view keyName, std::string_view value) {
	auto* data = Memory()->alloc<Object<std::string>>();
	data->set(value.data());
	m_Keys[keyName.data()] = data;
}

Blackboard::~Blackboard() {
	for(auto& item : m_Keys) {
		item.second->OnDestory();
		Memory()->dealloc(item.second);
	}
}