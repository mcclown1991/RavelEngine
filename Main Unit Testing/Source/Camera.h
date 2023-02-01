#pragma once
#include <Base Components/Camera.h>
#include <Behaviour/RavelBehaviour.h>

class FollowCam : public Camera{
public:
	FollowCam();
	~FollowCam();
	FollowCam* Clone();
	void Start() override;
};