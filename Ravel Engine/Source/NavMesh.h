#pragma once
#include <array>
#include <bitset>
#include "NavMeshBoundVolume.h"

struct Trapezoid {
public:
	Vector2 top_left, top_right, bottom_left, bottom_right;
	std::array<Trapezoid*, 4> _neighbour;
	std::bitset<4> _neighbourUsed;
	int _stateIndex;
};

class Navigation {
public:
	Navigation();
	void GenerateNavMesh(NavMeshBoundVolume* bounds);
};

Navigation* Navigator();