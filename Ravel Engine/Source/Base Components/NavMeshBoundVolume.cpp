#include "NavMeshBoundVolume.h"

NavMeshBoundVolume::NavMeshBoundVolume() : RavelBehaviour(), width(0), height(0) {
}

NavMeshBoundVolume::~NavMeshBoundVolume() {

}

void NavMeshBoundVolume::LoadFromFile(std::string const& file) {

}

void NavMeshBoundVolume::SetBounds(unsigned width, unsigned height)
{
	this->width = width;
	this->height = height;
}

void NavMeshBoundVolume::OnDestory() {
	this->~NavMeshBoundVolume();
}