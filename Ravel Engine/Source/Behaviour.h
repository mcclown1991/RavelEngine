#ifndef BEHAVIOUR_H
#define BEHAVIOUR_H

#include "Component.h"
#include <vector>

class Behaviour : public Component {
public:

	//Functions
	Behaviour();
	virtual ~Behaviour();

	template <typename T>
	T* GetComponent();

	template <typename T>
	std::vector<T*> GetComponentInChildren(bool includeInactive);

	virtual Behaviour* Clone() { return nullptr; }

	//Variables
	bool enabled;
	bool isActiveAndEnabled;
};

#endif

template<typename T>
inline T * Behaviour::GetComponent()
{
	return gameObject->GetComponent<T>();
}

template<typename T>
inline std::vector<T*> Behaviour::GetComponentInChildren(bool includeInactive)
{
	return std::vector<T*>();
}
