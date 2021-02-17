#include "Blackboard.h"

bool Blackboard::GetValueAsBool(std::string_view keyName) {
	auto* object = dynamic_cast<Object<bool>*>(m_Keys[keyName]);
	if (object)
		return object->data();
}

int Blackboard::GetValueAsInt(std::string_view keyName) {
	auto* object = dynamic_cast<Object<int>*>(m_Keys[keyName]);
	if (object)
		return object->data();
}

float Blackboard::GetValueAsFloat(std::string_view keyName) {
	auto* object = dynamic_cast<Object<float>*>(m_Keys[keyName]);
	if (object)
		return object->data();
}

double Blackboard::GetValueAsDouble(std::string_view keyName) {
	auto* object = dynamic_cast<Object<double>*>(m_Keys[keyName]);
	if (object)
		return object->data();
}

void Blackboard::SetValueAsBool(std::string_view keyName, bool value) {
	m_Keys[keyName] = Memory()->alloc<Object<bool>>();
}

void Blackboard::SetValueAsInt(std::string_view keyName, int value) {
	m_Keys[keyName] = Memory()->alloc<Object<int>>();
}

void Blackboard::SetValueAsFloat(std::string_view keyName, float value) {
	m_Keys[keyName] = Memory()->alloc<Object<float>>();
}

void Blackboard::SetValueAsDouble(std::string_view keyName, double value) {
	m_Keys[keyName] = Memory()->alloc<Object<double>>();
}
