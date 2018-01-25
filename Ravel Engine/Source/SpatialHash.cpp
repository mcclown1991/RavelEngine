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

void SpatialHash::HashCollider(Collider2D * col)
{
	int hash[4];
	hash[0] = Hash(col->rect->TopLeft());
	hash[1] = Hash(col->rect->TopRight());
	hash[2] = Hash(col->rect->BottomLeft());
	hash[3] = Hash(col->rect->BottomRight());
	
	col->hashkey[0] = hash[0];
	bool uq = true;
	for (int i = 1; i < 4; ++i) {
		uq = true;
		for (int j = 0; j < i; ++j) {
			if (hash[i] == col->hashkey[j])
				uq = false;
		}
		if (uq) col->hashkey[i] = hash[i];
		else col->hashkey[i] = NULL;
	}

	//add to map
	for (int key : col->hashkey) {
		std::vector<Collider2D*>& bucket = _map[key];
		if (key != NULL) {
			std::vector<Collider2D*>::iterator it = std::find(bucket.begin(), bucket.end(), col);
			if(it == bucket.end())
				//need to find dups	
				_map[key].push_back(col);
		}
	}
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
