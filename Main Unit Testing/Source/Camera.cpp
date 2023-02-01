#include "Camera.h"
#include <Systems/Input/Input.h>
#include <Game Object/GameObject.h>

FollowCam::FollowCam() {
	
}

FollowCam::~FollowCam() {
	
}

FollowCam* FollowCam::Clone() {
	return Memory()->alloc<FollowCam>();
}

void FollowCam::Start() {
	auto pawn =factory()->GetGameObject("Main Camera")->GetComponent<Camera>()->transform;
	
	GetInput()->BindAxis("MoveForward", GetInstanceID(), [this, pawn](float scale) {
		pawn->SetLocalPosition(pawn->GetLocalPosition() + pawn->up * scale * GetTime()->deltaTime);
	});

	GetInput()->BindAxis("MoveVertical", GetInstanceID(), [this, pawn](float scale) {
		std::cout << "Move : " << scale << std::endl;
		pawn->SetLocalPosition(pawn->GetLocalPosition() + pawn->right * scale * GetTime()->deltaTime);
	});
}
