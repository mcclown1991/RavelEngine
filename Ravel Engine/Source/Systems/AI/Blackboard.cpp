#include "Blackboard.h"

bool Blackboard::GetValueAsBool(std::string_view keyName) {
	auto* object = dynamic_cast<Object<bool>*>(m_Keys[keyName]);
	if (object)
		return object->data();
	return bool();
}

int Blackboard::GetValueAsInt(std::string_view keyName) {
	auto* object = dynamic_cast<Object<int>*>(m_Keys[keyName]);
	if (object)
		return object->data();
	return int();
}

float Blackboard::GetValueAsFloat(std::string_view keyName) {
	auto* object = dynamic_cast<Object<float>*>(m_Keys[keyName]);
	if (object)
		return object->data();
	return float();
}

double Blackboard::GetValueAsDouble(std::string_view keyName) {
	auto* object = dynamic_cast<Object<double>*>(m_Keys[keyName]);
	if (object)
		return object->data();
	return double();
}

std::string Blackboard::GetValueAsString(std::string_view keyName) {
	auto* object = dynamic_cast<Object<std::string>*>(m_Keys[keyName]);
	if (object)
		return object->data();
	return std::string();
}

void Blackboard::SetValueAsBool(std::string_view keyName, bool value) {
	auto* data = Memory()->alloc<Object<bool>>();
	data->set(value);
	m_Keys[keyName] = data;
}

void Blackboard::SetValueAsInt(std::string_view keyName, int value) {
	auto* data = Memory()->alloc<Object<int>>();
	data->set(value);
	m_Keys[keyName] = data;
}

void Blackboard::SetValueAsFloat(std::string_view keyName, float value) {
	auto* data = Memory()->alloc<Object<float>>();
	data->set(value);
	m_Keys[keyName] = data;
}

void Blackboard::SetValueAsDouble(std::string_view keyName, double value) {
	auto* data = Memory()->alloc<Object<double>>();
	data->set(value);
	m_Keys[keyName] = data;
}

void Blackboard::SetValueAsString(std::string_view keyName, std::string_view value) {
	auto* data = Memory()->alloc<Object<std::string_view>>();
	data->set(value);
	m_Keys[keyName] = data;
}