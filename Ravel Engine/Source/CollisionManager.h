#pragma once
#include <vector>
#include <algorithm>
#include "Collider2D.h"
#include "SpatialHash.h"

class CollisionManager {
public:
	CollisionManager();
	void InitCollisionMangaer();
	sInt32 AddCollider(Collider2D* col);
	void UpdateCollider(sInt32 colID);
	void Update();

private:
	//std::vector<std::pair<BoxCollider*, hgeRect*>> _colliders;
	std::vector<Collider2D*> _colliders;
	SpatialHash* _spatialMap;
};

CollisionManager* GetCollision();