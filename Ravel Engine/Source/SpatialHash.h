#pragma once

#include <unordered_map>
#include <vector>
#include "Collider2D.h"

class SpatialHash {
public:
	SpatialHash(int bucketsize);
	SpatialHash(int bucketsize_x, int bucketsize_y);
	~SpatialHash();

	void HashCollider(Collider2D* col);

private:
	int _x, _y;
	std::unordered_map<int, std::vector<Collider2D* >> _map;

	int Hash(Vector2 const& point);
};