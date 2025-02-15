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

	for (size_t i = 0; i < _colliders.size(); ++i) {
		if (_colliders[i]->gameObject->IsActive) {
			if (_colliders[i]->CursorIntersectionTest(mouse))
				if (GetMouseButtonDown(0))
					_colliders[i]->gameObject->SendMessage("OnMouseDown");

			/*for (int j = i + 1; j < _colliders.size(); ++j) {
				_colliders[i]->IntersectionTest(_colliders[j]);
			}*/

			//local bucket collision test
			std::vector<Collider2D*> temp = _spatialMap->GetBucket(i);
			for (Collider2D* col : temp) {
				if (_colliders[i] != col && col->gameObject->IsActive)
					if (_colliders[i]->IntersectionTest(col)) {
						_colliders[i]->gameObject->SendMessage("OnCollisionEnter2D", col);
						col->gameObject->SendMessage("OnCollisionEnter2D", _colliders[i]);
					}
			}
		}

		//neighbour bucket collision test
	}
}

void CollisionManager::OnExit()
{
	delete _spatialMap;
	_colliders.clear();
}

void CollisionManager::ClearState()
{
	_colliders.clear();
	_spatialMap->ClearHash();
}

std::vector<Collider2D*> CollisionManager::GetCollisionObjects() {
	return _colliders;
}

CollisionManager * GetCollision()
{
	static CollisionManager s;
	return(&s);
}
