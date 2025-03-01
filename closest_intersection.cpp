#include "closest_intersection.h"
#include "global_values.h"
#include "BVH/BoundingVolumeTree.h"
#include <iostream>

Intersection* get_closest_intersection(size_t triangles_size, std::vector<triangle3>* triangles, ray& raymond)
{
    
    Intersection* closest_intersection = nullptr;
    for (int n = 0; n < triangles_size; n++)
    {
        //closest_intersection points to intersection, but the intersection gets rewritten every time
        Intersection* intersection = ray_triangle_intersection(&(*triangles)[n], raymond);
        if (!intersection)
        {
            continue;
        }


        if (!closest_intersection)
        {
            closest_intersection = intersection;
            continue;
        }

        //determine which of the 2 points is closer to the image
        if ((intersection->_intersection_point - raymond.origin()).length() + _epsilon
            < (closest_intersection->_intersection_point - raymond.origin()).length())
        {
            closest_intersection = intersection;
        }
    }
    return closest_intersection;
}


Intersection* get_BVH_closest_intersection(BVHNode* current_node, ray& raymond)
{
    if (current_node->primitive != nullptr)
    {
        auto tmp = ray_triangle_intersection(current_node->primitive, raymond);
        return tmp;
    }

    double left_t = ray_aabb_intersection(current_node->left_child->box, raymond);
    double right_t = ray_aabb_intersection(current_node->right_child->box, raymond);

    Intersection* hit = nullptr;
    if(left_t != -1 and (right_t == -1 or left_t <= right_t))
    {
        hit = get_BVH_closest_intersection(current_node->left_child, raymond);
    }
    if (hit)
    {
        return hit;
    }
    if(right_t != -1)
    { 
        hit = get_BVH_closest_intersection(current_node->right_child, raymond);
    }
    return hit;
}