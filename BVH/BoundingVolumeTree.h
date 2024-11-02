#pragma once
#include "AABB.h"
#include "../Data/triangle3.h"

class BVHNode 
{	public:
	AABB* box = nullptr;
	triangle3* primitive = nullptr;
	BVHNode* left_child = nullptr;
	BVHNode* right_child = nullptr;

	BVHNode() {}
	~BVHNode() {
		delete box;
		delete primitive;
		delete left_child;
		delete right_child;
	}
};
