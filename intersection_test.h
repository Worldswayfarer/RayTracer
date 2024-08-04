#pragma once

#include "Intersection.h"


//Muller-Trumbore intersection
Intersection* ray_triangle_intersection(triangle3* triangle, ray& raymond);

double ray_aabb_intersection(AABB* box, ray& raymond);