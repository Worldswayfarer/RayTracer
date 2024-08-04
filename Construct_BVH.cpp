#include "Construct_BVH.h"
#include <vector>
#include <algorithm>

//sort primitives once at the start
BVHNode* construct_BVH(std::vector<triangle3>* primitives)
{
    std::vector<triangle3>* x_sorted = primitives;
    std::vector<triangle3>* y_sorted = primitives;
    std::vector<triangle3>* z_sorted = primitives;

    std::sort(x_sorted->begin(), x_sorted->end(), compareX);
    std::sort(y_sorted->begin(), y_sorted->end(), compareY);
    std::sort(z_sorted->begin(), z_sorted->end(), compareZ);



    return nullptr;
}

//would be much less effiecient, 
BVHNode* construct_node(std::vector<triangle3>* primitives, std::vector<triangle3>* x_sorted,
    std::vector<triangle3>* y_sorted, std::vector<triangle3>* z_sorted)
{
    BVHNode* new_node = new BVHNode();

    if (primitives->size() == 1)
    {
        new_node->primitive;
    }

    return nullptr;
}

BVHNode* construct_node(std::vector<triangle3>* primitives)
{
    BVHNode* new_node = new BVHNode();


    if (primitives->size() == 1)
    {
        new_node->primitive;
    }

    return nullptr;
}


AABB* construct_AABB()
{
    return nullptr;
}

bool compareX(triangle3& a, triangle3& b)
{
    return a.center().x() < b.center().x();
}
bool compareY(triangle3& a, triangle3& b)
{
    return a.center().y() < b.center().y();
}
bool compareZ(triangle3& a, triangle3& b)
{
    return a.center().z() < b.center().z();
}