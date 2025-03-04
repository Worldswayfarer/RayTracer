#include "example_scene.h"


std::tuple<std::vector<triangle3>*, int> build_cube(point3 center, size_t size, RGB_Material material)
{
    //triangles per cube
    int triangle_count = 12;
    vector3 up = vector3(0, 1, 0) * (size/2.0);
    vector3 right = vector3(1, 0, 0) * (size/2.0);
    vector3 back = vector3(0, 0, -1) * (size / 2.0);

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

vector3 random_direction()
{
    return vector3(static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (1 - -1))),
        static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (1 - -1))),
        static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (1 - -1))));
}

std::tuple<std::vector<triangle3>*, int> build_triangles(point3 center, size_t size, RGB_Material material) {
    std::vector<triangle3>* triangles = new std::vector<triangle3>;
    int triangle_count = 0;

    point3 left = center + random_direction();
    point3 right = center + random_direction();
    triangles->push_back(triangle3(center, left, right));
    (*triangles)[0].setMaterial(material);
    return std::make_tuple(triangles, triangle_count);

}

std::tuple < std::vector<triangle3>*, int> build_plane(point3 center, size_t size)
{
    RGB_Material material = RGB_Material(color3(static_cast <float> (rand()) / static_cast <float> (RAND_MAX),
        static_cast <float> (rand()) / static_cast <float> (RAND_MAX),
        static_cast <float> (rand()) / static_cast <float> (RAND_MAX)),
        1, 0.5, 0.5, 1);
    size_t triangle_count = 2;
    std::vector<triangle3>* triangles = new std::vector<triangle3>;
    vector3 right = vector3(1, 0, 0) * (size / 2);
    vector3 back = vector3(0, 0, -1) * (size / 2);
    point3 left_front = center - right - back;
    point3 right_front = center + right - back;
    point3 left_back = center - right + back;
    point3 right_back = center + right + back;
    triangles->push_back(triangle3(left_front, right_front, left_back));
    triangles->push_back(triangle3(left_back, right_back, right_front));
    for (int index = 0; index < triangle_count; index++)
    {
        (*triangles)[index].setMaterial(material);
    }
    return std::make_tuple(triangles, triangle_count);
}

std::tuple<std::vector<triangle3>*, int> build_scene(size_t cube_count)
{

    std::vector<triangle3>* triangles  = new std::vector<triangle3>;
    size_t triangle_count = 0;
    
    
    for (int x = 0; x < cube_count; x++)
    {
        std::vector<triangle3>* add;
        size_t count;
        
        RGB_Material material = RGB_Material(color3(static_cast <float> (rand()) / static_cast <float> (RAND_MAX),
            static_cast <float> (rand()) / static_cast <float> (RAND_MAX) ,
            static_cast <float> (rand()) / static_cast <float> (RAND_MAX)),
            1, 0.5, 0.5, 1);
        std::tie(add, count) = build_cube(point3(-4 + rand() % 8,
            -3 + rand() % 6,
            -8 + rand() % 4),
            rand() % 3, material);
        
        triangles->insert(triangles->end(), add->begin(), add->end());
        triangle_count += count;
    }


    return std::make_tuple(triangles, triangle_count);
}
