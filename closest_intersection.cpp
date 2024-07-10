#include "closest_intersection.h"


Intersection* get_closest_intersection(double focal_length, point3 pixel_point,
    size_t triangles_size, std::vector<triangle3>* triangles, ray& raymond)
{
    constexpr double epsilon = 0.00001;
    Intersection* closest_intersection = nullptr;
    for (int n = 0; n < triangles_size; n++)
    {
        //closest_intersection points to intersection, but the intersection gets rewritten every time
        Intersection* intersection = ray_triangle_intersection(&(*triangles)[n], raymond);
        if (!intersection)
        {
            continue;
        }

        vector3 distance_ray_point = raymond.direction() * intersection->_ray_t;
        // intersection is behind the image
        if (distance_ray_point.length() < focal_length) { continue; }


        if (!closest_intersection)
        {
            closest_intersection = intersection;
            continue;
        }

        //determine which of the 2 points is closer to the image
        if ((intersection->_intersection_point - pixel_point).length() + epsilon
            < (closest_intersection->_intersection_point - pixel_point).length())
        {
            closest_intersection = intersection;
        }
    }
    return closest_intersection;
}

Intersection* get_closest_intersection(size_t triangles_size, std::vector<triangle3>* triangles, ray& raymond)
{
    constexpr double epsilon = std::numeric_limits<double>::epsilon();
    Intersection* closest_intersection = nullptr;
    for (int n = 0; n < triangles_size; n++)
    {
        //closest_intersection points to intersection, but the intersection gets rewritten every time
        Intersection* intersection = ray_triangle_intersection(&(*triangles)[n], raymond);
        if (intersection)
        {
            return intersection;
        }
    }
    return closest_intersection;
}
