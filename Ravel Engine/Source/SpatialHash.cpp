#include "SpatialHash.h"

SpatialHash::SpatialHash(int bucketsize) : _x(bucketsize), _y(bucketsize), _map()
{
}

SpatialHash::SpatialHash(int bucketsize_x, int bucketsize_y) : _x(bucketsize_x), _y(bucketsize_y), _map()
{
}

SpatialHash::~SpatialHash()
{
}

size_t SpatialHash::HashCollider(Collider2D * col)
{
	return Hash(col->transform->position);
}

void SpatialHash::InsertCollider(Collider2D * col)
{
	_map[col->hashkey].push_back(col);
}

void SpatialHash::InsertCollider(Collider2D * col, size_t hash)
{
	_map[hash].push_back(col);
}

void SpatialHash::InsertColliderWithUpdate(Collider2D * col, size_t new_hash)
{
	//find old collider in map
	if (_map.size() == 0) {
		std::cout << "Map is empty... But I will still insert collider in" << std::endl;
		InsertCollider(col, new_hash);
		return;
	}
	if (_map.find(col->hashkey) == _map.end()) {
		std::cout << "Collider does not exist in map, I will insert in instead" << std::endl;
		InsertCollider(col, new_hash);
		return;
	}
	std::vector<Collider2D*>& bucket = _map[col->hashkey];
	std::vector<Collider2D*>::iterator it = std::find(bucket.begin(), bucket.end(), col);
	if (it != bucket.end())
		bucket.erase(it);

	//Insert at new
	InsertCollider(col, new_hash);

	//Next thing is pobably to insert the whole collider instead of a position, this might be more accurate but compute expensive thou
}

void SpatialHash::RemoveCollider(Collider2D * col)
{
	if (_map.size() == 0) return;
	if (_map.find(col->hashkey) == _map.end()) return;
	std::vector<Collider2D*>& bucket = _map[col->hashkey];
	std::vector<Collider2D*>::iterator it = std::find(bucket.begin(), bucket.end(), col);
	if (it != bucket.end())
		bucket.erase(it);
}

void SpatialHash::ClearHash()
{
	_map.clear();
}

std::vector<Collider2D*> const& SpatialHash::GetBucket(int key)
{
	return _map[key];
}

int SpatialHash::Hash(Vector2 const& point)
{
	int x = (int)std::ceil(point.x / (float)_x);
	int y = (int)std::ceil(point.y / (float)_y);
	int power = 1;
	if (y != 0) {
		power = (int)pow(10.0, (double)((int)log10((double)y)) + 1.0);
	}

	return x * power + y;
}
