#include "triangle3.h"

void triangle3::setMaterial(RGB_Material material)
{
    _material = material;
}

//Muller-Trumbore intersection
Intersection* triangle3::ray_triangle_intersection(ray& raymond)
{
    constexpr double epsilon = std::numeric_limits<double>::epsilon();

    vector3 edge1 = _b - _a;
    vector3 edge2 = _c - _a;

    vector3 ray_cross_e2 = cross_product(raymond.direction(), edge2);
    double det = dot_product(edge1, ray_cross_e2);

    if (det > -epsilon && det < epsilon)
        return {};    // Ray is parallel.

    double inv_det = 1.0 / det;
    vector3 s = raymond.origin() - _a;
    double u = inv_det * dot_product(s, ray_cross_e2);

    if (u < 0 || u > 1)
        return {}; // No intersection.

    vector3 s_cross_e1 = cross_product(s, edge1);
    double v = inv_det * dot_product(raymond.direction(), s_cross_e1);

    if (v < 0 || u + v > 1)
        return {}; // No intersection.

    // At this stage we can compute t to find out where the intersection point is on the line.
    double t = inv_det * dot_product(edge2, s_cross_e1);

    if (t > epsilon) // Ray intersection.
    {
        point3 intersection_point = raymond.origin() + t * raymond.direction();
        Intersection* inter = new Intersection(_material, unit_vector(cross_product(edge1, edge2)), intersection_point, t);
        return  inter;
    }
    else // Intersection is in the "wrong" direction.
        return {};
}
