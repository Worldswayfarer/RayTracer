#pragma once

#include <vector>

#include "BoundingVolumeTree.h"
#include "AABB.h"

BVHNode* construct_BVH(std::vector<triangle3>* primitives);