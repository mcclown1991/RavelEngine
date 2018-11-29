#pragma once
#include "RavelMath.h"
#include "RavelBehaviour.h"

class NavMeshBoundVolume : public RavelBehaviour {
public :
	NavMeshBoundVolume();
	virtual ~NavMeshBoundVolume();
	virtual NavMeshBoundVolume* Clone() {
		return Memory()->alloc<NavMeshBoundVolume>();
	}

	virtual void LoadFromFile(std::string const& filename);
	virtual void OnDestory() { this->~NavMeshBoundVolume(); }

	void SetBounds(unsigned width, unsigned height);

private:
	unsigned width, height;
};