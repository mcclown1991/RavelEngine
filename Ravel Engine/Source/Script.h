#ifndef SCRIPT_H
#define SCRIPT_H

#include "Component.h"
#include "GameObject.h"
#include "ScriptManager.h"
#include "RavelEngine.h"

class Script : public RavelBehaviour {
public:
	Script();
	virtual ~Script();
	virtual Script* Clone() {
		return Memory()->alloc<Script>();
	}

	virtual void LoadFromFile(std::string const& file);

	virtual void Update();
	virtual void OnDestory();

	void LoadScript(std::string const& filename);

	template<typename T>
	void CallEvent(const std::string name, const T t_id) {
		if(m_Filename.data())
			GetScriptManager()->CallEvent(m_Filename.data(), name, m_OwnerID, t_id);
	}

private:
	std::string_view m_Filename;
	std::size_t m_OwnerID;
};

#endif