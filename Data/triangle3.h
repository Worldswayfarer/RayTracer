#pragma once

#ifndef TRIANGLE
#define TRIANGLE

#include "ray.h"
#include "RGB_Material.h"

#include "../Intersection.h"

class triangle3 
{
public:
    triangle3() = default;

    triangle3(const point3 a, const point3 b, const point3 c) : _a(a), _b(b), _c(c) 
    {
        float x = (_a.x() + _b.x() + _c.x()) / 3;
        float y = (_a.y() + _b.y() + _c.y()) / 3;
        float z = (_a.z() + _b.z() + _c.z()) / 3;
        _center = point3(x, y, z);
    }

    const point3& a() const { return _a; }
    const point3& b() const { return _b; }
    const point3& c() const { return _c; } 
    const point3& center() const { return _center; }

    RGB_Material _material;

    void setMaterial(RGB_Material material);

private:
    point3 _a;
    point3 _b;
    point3 _c;  
    point3 _center;
};
#endif
