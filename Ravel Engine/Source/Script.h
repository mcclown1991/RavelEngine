#ifndef SCRIPT_H
#define SCRIPT_H

#include "Component.h"
#include "GameObject.h"
#include "ScriptManager.h"

class Script : public Component {
public:
	Script();
	virtual ~Script();

	virtual void OnStart();
	virtual void Update();
	virtual void OnDestory();

	void LoadScript(std::string const& filename);

	template<typename T>
	void CallEvent(const std::string name, const T t_id) {
		GetScriptManager()->CallEvent(m_Filename, name, m_OwnerID, t_id);
	}

private:
	std::string m_Filename;
	std::size_t m_OwnerID;
};

#endif