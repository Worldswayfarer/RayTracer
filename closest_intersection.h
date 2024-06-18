#pragma once

#include "Intersection.h"
#include "triangle3.h"
#include "ray.h"
#include "intersection_test.h"
#include <vector>
#include <limits>

//Visibility test
Intersection* get_closest_intersection(double focal_length, point3 pixel_point,
    size_t triangles_size, std::vector<triangle3>* triangles, ray& raymond);

//For "shadow" rays.
Intersection* get_closest_intersection(size_t triangles_size, std::vector<triangle3>* triangles, ray& raymond);