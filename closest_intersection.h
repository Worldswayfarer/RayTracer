#pragma once

#include "Intersection.h"
#include "triangle3.h"
#include "ray.h"
#include "intersection_test.h"
#include <vector>
#include <limits>
#include "BoundingVolumeTree.h"

//Visibility test
Intersection* get_closest_intersection(size_t triangles_size, std::vector<triangle3>* triangles, ray& raymond);


//BVH part
Intersection* get_BVH_closest_intersection(BVHNode* current_node, ray& raymond);