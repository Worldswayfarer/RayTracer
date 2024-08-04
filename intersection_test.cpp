#include "intersection_test.h"
#include "global_values.h"

//Möller-Trumbore intersection
Intersection* ray_triangle_intersection(triangle3* triangle, ray& raymond)
{

    vector3 edge1 = triangle->b() - triangle->a();
    vector3 edge2 = triangle->c() - triangle->a();

    vector3 ray_cross_e2 = cross_product(raymond.direction(), edge2);
    double det = dot_product(edge1, ray_cross_e2);

    if (det > -_epsilon && det < _epsilon)
        return nullptr;    // Ray is parallel.
    
    double inv_det = 1.0 / det;
    vector3 s = raymond.origin() - triangle->a();
    double u = inv_det * dot_product(s, ray_cross_e2);

    if (u < 0 || u > 1)
        return nullptr; // No intersection.

    vector3 s_cross_e1 = cross_product(s, edge1);
    double v = inv_det * dot_product(raymond.direction(), s_cross_e1);

    if (v < 0 || u + v > 1)
        return nullptr; // No intersection.

    // At this stage we can compute t to find out where the intersection point is on the line.
    double t = inv_det * dot_product(edge2, s_cross_e1);

    if (t > _epsilon) // Ray intersection.
    {
        point3 intersection_point = raymond.origin() + t * raymond.direction();
        Intersection* inter = new Intersection(triangle->_material, unit_vector(cross_product(edge1, edge2)), intersection_point, t);
        return  inter;
    }
    else // Intersection is in the "wrong" direction.
        return nullptr;
}

double ray_aabb_intersection(AABB* box, ray& raymond)
{
    vector3 inverse_direction = 1 / raymond.direction();
    vector3 t_min = (box->_min - raymond.origin()) * inverse_direction;
    vector3 t_max = (box->_max - raymond.origin()) * inverse_direction;

    vector3 t1 = minimum(t_min, t_max);
    vector3 t2 = maximum(t_min, t_max);

    double t_near = t1[0] > t1[1] ? t1[0] : t1[1];
    t_near = t1[1] > t1[2] ? t1[1] : t1[2];
    double t_far = t1[0] < t1[1] ? t1[0] : t1[1];
    t_far = t1[1] < t1[2] ? t1[1] : t1[2];

    if (t_near <= t_far and t_far >= 0 and t_near > _epsilon)
    {
        return  t_near;
    }
    return 0;
}