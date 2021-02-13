#include "Blackboard.h"

bool Blackboard::GetBlackboardValueAsBool(std::string const& keyID)
{
	return m_Keys[keyID];
}

int Blackboard::GetBlackboardValueAsInt(std::string const& keyID)
{
	return (int)m_Keys[keyID];
}

float Blackboard::GetBlackboardValueAsFloat(std::string const& keyID)
{
	return 0.f; //(float)m_Keys[keyID];
}

double Blackboard::GetBlackboardValueAsDouble(std::string const& keyID)
{
	return 0.0; //(double)m_Keys[keyID];
}
