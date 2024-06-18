#include "example_scene.h"


std::tuple<std::vector<triangle3>*, int> build_cube(point3 center, size_t size, RGB_Material material)
{
    //triangles per cube
    int triangle_count = 12;
    vector3 up = vector3(0, 1, 0) * (size/2);
    vector3 right = vector3(1, 0, 0) * (size/2);
    vector3 back = vector3(0, 0, -1) * (size / 2);

    //front side
    point3 left_front = center + up - right - back;
    point3 right_front = center + up + right - back;
    point3 left_down_front = center - up - right - back;
    point3 right_down_front = center - up + right - back;
    //backside
    point3 left_back = center + up - right + back;
    point3 right_back = center + up + right + back;
    point3 left_down_back = center - up - right + back;
    point3 right_down_back = center - up + right + back;

    std::vector<triangle3>* triangles = new std::vector<triangle3>;
    //front
    triangles->push_back(triangle3(left_front, right_front, left_down_front));
    triangles->push_back(triangle3(right_down_front, right_front, left_down_front));
    //back
    triangles->push_back(triangle3(left_back, right_back, left_down_back));
    triangles->push_back(triangle3(right_down_back, right_back, left_down_back));
    //left
    triangles->push_back(triangle3(left_front, left_back, left_down_front));
    triangles->push_back(triangle3(left_down_back, left_back, left_down_front));
    //right
    triangles->push_back(triangle3(right_front, right_back, right_down_front));
    triangles->push_back(triangle3(right_down_back, right_back, right_down_front));
    //top
    triangles->push_back(triangle3(left_front, right_back, left_back));
    triangles->push_back(triangle3(left_front, right_front, right_back));
    //bottom
    triangles->push_back(triangle3(left_down_front, right_down_front, left_down_back));
    triangles->push_back(triangle3(left_down_back, right_down_front, right_down_back));


    for (int index = 0; index < triangle_count; index++)
    {
        (*triangles)[index].setMaterial(material);
    }
    return std::make_tuple(triangles, triangle_count);
}



std::tuple<std::vector<triangle3>*, int> build_scene(size_t cube_count)
{
    /*
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
    */
    using namespace std;
    vector<triangle3>* triangles  = new std::vector<triangle3>;
    size_t triangle_count = 0;
    RGB_Material material = RGB_Material(color3(0, 1, 1), 0.3, 0.5, 0.5, 1);
    
    for (int x = 0; x < cube_count; x++)
    {
        vector<triangle3>* add;
        size_t count;
        std::tie(add, count) = build_cube(point3(rand() % 8 - 4, rand() % 8 - 4, -(rand() % 4) - 3), rand() % 3 + 1, material);
        triangles->insert(triangles->end(), add->begin(), add->end());
        triangle_count += count;
    }


    return std::make_tuple(triangles, triangle_count);
}
