#pragma once

#ifndef TRIANGLE
#define TRIANGLE

#include "ray.h"
#include <limits>

class triangle3 {
public:
    triangle3() {}

    triangle3(const point3 a, const point3 b, const point3 c) : _a(a), _b(b), _c(c) {}

    const point3& a() const { return _a; }
    const point3& b() const { return _b; }
    const point3& c() const { return _c; } 
    point3* ray_triangle_intersection(ray& raymond)
    {
        constexpr double epsilon = std::numeric_limits<double>::epsilon();

        vector3 edge1 = _b - _a;
        vector3 edge2 = _c - _a;
        vector3 ray_cross_e2 = cross_product(raymond.direction(), edge2);
        double det = dot_product(edge1, ray_cross_e2);

        if (det > -epsilon && det < epsilon)
            return {};    // This ray is parallel to this triangle.

        double inv_det = 1.0 / det;
        vector3 s = raymond.origin() - _a;
        double u = inv_det * dot_product(s, ray_cross_e2);

        if (u < 0 || u > 1)
            return {};

        vector3 s_cross_e1 = cross_product(s, edge1);
        double v = inv_det * dot_product(raymond.direction(), s_cross_e1);

        if (v < 0 || u + v > 1)
            return {};

        // At this stage we can compute t to find out where the intersection point is on the line.
        double t = inv_det * dot_product(edge2, s_cross_e1);

        if (t > epsilon) // ray intersection
        {
            point3 intersection(raymond.direction() + raymond.origin() * t);
            return  &intersection;
        }
        else // This means that there is a line intersection but not a ray intersection.
            return {};
    }

private:
    point3 _a;
    point3 _b;
    point3 _c;
};

#endif