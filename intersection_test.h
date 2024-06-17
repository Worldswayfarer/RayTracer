#pragma once

#include "Intersection.h"


//Muller-Trumbore intersection
Intersection* ray_triangle_intersection(triangle3* triangle, ray& raymond);