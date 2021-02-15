#include "Blackboard.h"

bool Blackboard::GetBlackboardValueAsBool(std::string const& keyID) {
	return m_Keys[keyID];
}

int Blackboard::GetBlackboardValueAsInt(std::string const& keyID) {
	return (int)m_Keys[keyID];
}

float Blackboard::GetBlackboardValueAsFloat(std::string const& keyID) {
	return dynamic_cast<Object<float>*>(m_Keys[keyID])->data();
}

double Blackboard::GetBlackboardValueAsDouble(std::string const& keyID) {
	return dynamic_cast<Object<double>*>(m_Keys[keyID])->data();
}
