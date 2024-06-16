#include "example_scene.h"

std::tuple<triangle3*, int> build_scene()
{
    //triangles in the scene
    int triangle_count = 12;

    //examplecube

    //front side
    point3 left_front = point3(-4, -1, -2);
    point3 right_front = point3(-2, -1, -2);
    point3 left_down_front = point3(-4, -3, -2);
    point3 right_down_front = point3(-2, -3, -2);
    //backside
    point3 left_back = point3(-4, -1, -4);
    point3 right_back = point3(-2, -1, -4);
    point3 left_down_back = point3(-4, -3, -4);
    point3 right_down_back = point3(-2, -3, -4);

    triangle3* triangles = new triangle3[triangle_count];
    //front
    triangles[0] = triangle3(left_front, right_front, left_down_front);
    triangles[1] = triangle3(right_down_front, right_front, left_down_front);
    //back
    triangles[2] = triangle3(left_back, right_back, left_down_back);
    triangles[3] = triangle3(right_down_back, right_back, left_down_back);
    //left
    triangles[4] = triangle3(left_front, left_back, left_down_front);
    triangles[5] = triangle3(left_down_back, left_back, left_down_front);
    //right
    triangles[6] = triangle3(right_front, right_back, right_down_front);
    triangles[7] = triangle3(right_down_back, right_back, right_down_front);
    //top
    triangles[8] = triangle3(left_front, right_back, left_back);
    triangles[9] = triangle3(left_front, right_front, right_back);
    //bottom
    triangles[10] = triangle3(left_down_front, right_down_front, left_down_back);
    triangles[11] = triangle3(left_down_front, right_down_front, right_down_back);

    RGB_Material material = RGB_Material(color3(0, 1, 1), 0.3, 0.5, 0.5, 1);

    for (int index = 0; index < triangle_count; index++)
    {
        triangles[index].setMaterial(material);
    }

    return std::make_tuple(triangles, triangle_count);
}
