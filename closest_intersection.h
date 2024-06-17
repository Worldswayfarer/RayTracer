#pragma once

#include "Intersection.h"
#include "triangle3.h"
#include "ray.h"
#include "intersection_test.h"

Intersection* get_closest_intersection(double focal_length, point3 pixel_point,
    size_t triangles_size, triangle3* triangles, ray& raymond);