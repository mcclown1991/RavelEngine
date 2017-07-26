#pragma once
#include <vector>
#include <algorithm>
#include "BoxCollider.h"

class CollisionManager {
public:
	CollisionManager();
	sInt32 AddCollider(BoxCollider* col, Vector2 size);
	void Update();

private:
	//std::vector<std::pair<BoxCollider*, hgeRect*>> _colliders;
	
};

CollisionManager* GetCollision();