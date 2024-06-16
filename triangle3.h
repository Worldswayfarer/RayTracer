#pragma once

#ifndef TRIANGLE
#define TRIANGLE

#include "ray.h"
#include "RGB_Material.h"
#include <limits>
#include "Intersection.h"

class triangle3 
{
public:
    triangle3() = default;

    triangle3(const point3 a, const point3 b, const point3 c) : _a(a), _b(b), _c(c) {}

    const point3& a() const { return _a; }
    const point3& b() const { return _b; }
    const point3& c() const { return _c; } 

    RGB_Material _material;

    void setMaterial(RGB_Material material);


    //Muller-Trumbore intersection
    Intersection* ray_triangle_intersection(ray& raymond);


private:
    point3 _a;
    point3 _b;
    point3 _c;  
};

#endif