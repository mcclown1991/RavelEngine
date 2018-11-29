#include "NavMesh.h"
#include "SceneManager.h"

Navigation * Navigator()
{
	static Navigation s;
	return(&s);
}


Navigation::Navigation()
{
}

void Navigation::GenerateNavMesh(NavMeshBoundVolume * bounds)
{
	// generate first trapezoid which is the bounding box
	std::vector<size_t> obj = SceneManagement()->GetSceneObjects();
	for (size_t ids : obj) {
		factory()->GetGameObject(ids);
	}
}

