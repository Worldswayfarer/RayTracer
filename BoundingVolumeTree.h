#pragma once
#include "AABB.h"
#include "triangle3.h"

struct BVHNode 
{
	AABB* box = nullptr;
	triangle3* primitive = nullptr;
	BVHNode* left_child = nullptr;
	BVHNode* right_child = nullptr;
};
