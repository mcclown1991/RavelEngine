#pragma once

#include <unordered_map>
#include <vector>
#include "Collider2D.h"

class SpatialHash {
public:
	SpatialHash(int bucketsize);
	SpatialHash(int bucketsize_x, int bucketsize_y);
	~SpatialHash();

	size_t HashCollider(Collider2D* col);
	void InsertCollider(Collider2D* col);
	void InsertCollider(Collider2D* col, size_t hash);
	void InsertColliderWithUpdate(Collider2D* col, size_t new_hash);
	void RemoveCollider(Collider2D* col);
	void ClearHash();

	std::vector<Collider2D*> const& GetBucket(int key);

private:
	int _x, _y;
	std::unordered_map<int, std::vector<Collider2D* >> _map;

	int Hash(Vector2 const& point);
};