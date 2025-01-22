#include "Tasks.h"

#include "BehaviourTree.h"
#include "ComponentHeader.h"

BTMoveToTask::BTMoveToTask() {
	GetScriptManager()->AddFunction("MoveTo", [](lua_State* L) {
		size_t id = luaL_checkinteger(L, -3);
		std::string targetkey = luaL_checkstring(L, -2);
		float acceptable_radius = luaL_checknumber(L, -1);

		auto& gameObject = factory()->GetGameObject(id);
		if (!gameObject)
			return 0;
		auto* bt = gameObject->GetComponent<BehaviourTree>();
		if (!bt || !bt->GetBlackboard())
			return 0;
		//auto object = bt->GetBlackboard()->GetValueAsObject<size_t>(targetkey);
		//size_t targetId = object.value();
		std::string targetId = bt->GetBlackboard()->GetValueAsString(targetkey);
		auto& target = factory()->GetGameObject(targetId);

		// Move logic
		auto vector = target->transform->position - gameObject->transform->position;
		if (vector.Length() < acceptable_radius) {
			bt->GetRunningNode()->SetResult(true);
			return 0;
		}
		auto* controller = gameObject->GetComponent<AIController>();
		controller->PushMoveRequest(vector.Normalized());
		bt->GetRunningNode()->SetResult(false);
		return 0;
	});
}

BTMoveToTask::~BTMoveToTask() {
	
}

bool BTMoveToTask::Execute() {
	AssignRunningNode();
	// execute move to key
	parent->ExecuteTask(nodeName);
	std::cout << "result : " << (result ? "true" : "false") << std::endl;
	return result;
}
