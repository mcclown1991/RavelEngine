#include "Tasks.h"

#include "BehaviourTree.h"
#include "ComponentHeader.h"

BTMoveToTask::BTMoveToTask() {
	GetScriptManager()->AddFunction("MoveTo", [](lua_State* L) {
		size_t id = luaL_checklong(L, -3);
		std::string targetkey = luaL_checkstring(L, -2);
		std::string speedkey = luaL_checkstring(L, -1);

		auto& gameObject = factory()->GetGameObject(id);
		if (!gameObject)
			return 0;
		auto* bt = gameObject->GetComponent<BehaviourTree>();
		if (!bt || !bt->GetBlackboard())
			return 0;
		//auto object = bt->GetBlackboard()->GetValueAsObject<size_t>(targetkey);
		//size_t targetId = object.value();
		std::string targetId = bt->GetBlackboard()->GetValueAsString(targetkey);
		float speed = bt->GetBlackboard()->GetValueAsFloat(speedkey);
		auto& target = factory()->GetGameObject(targetId);

		// Move logic
		auto* transform = gameObject->transform;
		auto* targetTransform = target->transform;

		auto direction = targetTransform->position - transform->position;
		direction.Normalize();

		transform->SetPosition(transform->position + (direction * speed));
		
		return 0;
	});
}

BTMoveToTask::~BTMoveToTask() {
	
}

bool BTMoveToTask::Execute() {
	// execute move to key
	parent->ExecuteTask(nodeName);
	return true;
}
