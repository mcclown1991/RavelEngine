#pragma once
#include <vector>
#include <algorithm>
#include "Collider2D.h"

class CollisionManager {
public:
	CollisionManager();
	sInt32 AddCollider(Collider2D* col);
	void Update();

private:
	//std::vector<std::pair<BoxCollider*, hgeRect*>> _colliders;
	std::vector<Collider2D*> _colliders;
};

CollisionManager* GetCollision();