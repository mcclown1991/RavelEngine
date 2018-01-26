#include "CollisionManager.h"
#include "Input.h"

CollisionManager::CollisionManager()
{
}

void CollisionManager::InitCollisionMangaer()
{
	_spatialMap = new SpatialHash(10);
}

sInt32 CollisionManager::AddCollider(Collider2D * col)
{
	_colliders.push_back(col);
	return _colliders.size() - 1;
}

void CollisionManager::UpdateCollider(sInt32 colID)
{
	size_t hash = _spatialMap->HashCollider(_colliders[colID]);
	_spatialMap->InsertColliderWithUpdate(_colliders[colID], hash);
	_colliders[colID]->hashkey = hash;
}

void CollisionManager::Update()
{
	// Update mouse hovers
	Vector2 mouse;
	GetMousePos(mouse.x, mouse.y);

	for (int i = 0; i < _colliders.size(); ++i) {
		_colliders[i]->CursorIntersectionTest(mouse);

		/*for (int j = i + 1; j < _colliders.size(); ++j) {
			_colliders[i]->IntersectionTest(_colliders[j]);
		}*/

		//local bucket collision test
		std::vector<Collider2D*> temp = _spatialMap->GetBucket(i);
		for (Collider2D* col : temp) {
			if(_colliders[i] != col)
				_colliders[i]->IntersectionTest(col);
		}


		//neighbour bucket collision test
	}

	//for (auto& iter : _colliders) {
	//	Vector2 p(iter.second->x1, iter.second->y1);
	//	Vector2 q(iter.second->x2, iter.second->y2);

	//	Vector2 r = iter.first->transform->GetPosition(); // new position
	//	//next find the with and height

	//	Vector2 displace(r - p);

	//	//Matrix3x3 M = iter.first->transform->GetTransforms();
	//	//p = M * p;
	//	//q = M * q;

	//	iter.second->x1 = p.x + displace.x;
	//	iter.second->y1 = p.y + displace.y;
	//	iter.second->x2 = q.x + displace.x;
	//	iter.second->x2 = q.y + displace.y;
	//}
	//for (unsigned i = 0; i < _colliders.size(); ++i) {
	//	for (unsigned j = 0; j < _colliders.size(); ++j) {
	//		if (i == j) break;
	//		if (_colliders[i].second->Intersect(_colliders[j].second)) {
	//			_colliders[i].first->OnCollision(_colliders[j].first);
	//		}
	//	}
	//}
}

CollisionManager * GetCollision()
{
	static CollisionManager s;
	return(&s);
}
