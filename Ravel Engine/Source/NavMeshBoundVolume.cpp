#include "NavMeshBoundVolume.h"

NavMeshBoundVolume::NavMeshBoundVolume()
{
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