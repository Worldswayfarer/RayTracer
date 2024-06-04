#pragma once

#ifndef TRIANGLE
#define TRIANGLE

#include "ray.h"
#include "RGB_Material.h"
#include <limits>

struct Intersection {
public:

    RGB_Material _material;
    //expect vector to be normalized
    vector3 _normal;
    point3 _intersection_point;
    double _ray_t;

    Intersection(const RGB_Material& _material, const vector3& _normal, const point3& _intersection_point, double _ray_t)
        : _material(_material), _normal(_normal), _intersection_point(_intersection_point), _ray_t(_ray_t)
    {
    }

    Intersection() = default;
};

class triangle3 {
public:
    triangle3() = default;

    triangle3(const point3 a, const point3 b, const point3 c) : _a(a), _b(b), _c(c) {}

    const point3& a() const { return _a; }
    const point3& b() const { return _b; }
    const point3& c() const { return _c; } 

    RGB_Material _material;

    void setMaterial(RGB_Material material)
    {
        _material = material;
    }

    Intersection* ray_triangle_intersection(ray& raymond)
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
            return {}; // The intersection point doesnt lie in the triangle.

        vector3 s_cross_e1 = cross_product(s, edge1);
        double v = inv_det * dot_product(raymond.direction(), s_cross_e1);

        if (v < 0 || u + v > 1)
            return {}; // The intersection point doesnt lie in the triangle.

        // At this stage we can compute t to find out where the intersection point is on the line.
        double t = inv_det * dot_product(edge2, s_cross_e1);

        if (t > epsilon) // ray intersection
        {
            point3 intersection_point = raymond.origin() + t * raymond.direction();
            Intersection inter = Intersection(_material, unit_vector(cross_product(edge1, edge2)), intersection_point, t);
            return  &inter;
        }
        else // This means that there is a line intersection but not a ray intersection.
            return {};
    }

private:
    point3 _a;
    point3 _b;
    point3 _c;
public:



    
};

#endif