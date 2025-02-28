#pragma once

#ifndef INTERSECTION
#define INTERSECTION
#endif

#include "Data/triangle3.h"
#include "BVH/AABB.h"
#include "Data/ray.h"
#include "Data/vector3.h"
#include "algorithm"

struct Intersection {
public:

    RGB_Material _material;
    //expect vector to be normalized
    vector3 _normal;
    point3 _intersection_point;
    double _ray_t;



    Intersection() = default;

    Intersection(const RGB_Material material, const vector3& normal, const point3& intersection_point, double ray_t)
        : _material(material), _normal(normal), _intersection_point(intersection_point), _ray_t(ray_t)
    {
    }
};