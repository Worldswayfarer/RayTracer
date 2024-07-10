#pragma once
#include "raytracer.h"
#include "triangle3.h"
#include "RGB_Material.h"
#include <tuple>

#include <algorithm>
#include <cmath>
#include "example_scene.h"
#include "Intersection.h"
#include "closest_intersection.h"
#include <vector>

std::tuple<std::vector<triangle3>*, int> get_triangles()
{
    return build_scene(3);
}


color3 calculate_light(size_t triangles_size, std::vector<triangle3>* triangles, Intersection* intersection, point3 light_source, ray raymond)
{
    RGB_Material material = intersection->_material;

    color3 source_light(1, 1, 1);
    color3 light_ambiente(0.15, 0.15, 0.15);

    color3 ambiente_component = light_ambiente * material._ambiente * material._object_color;
  
    vector3 normal;

    //points towards the lightsource
    vector3 light_direction = unit_vector(light_source - intersection->_intersection_point);
    ray shadow_ray = ray(intersection->_intersection_point, light_direction);

    
    //Test if the triangle is illuminated
    Intersection*  shadow_intersection = get_closest_intersection(triangles_size, triangles, shadow_ray);
    if (shadow_intersection != nullptr)
    {
        return ambiente_component;
    }
    
    if (dot_product(intersection->_normal, light_direction) < 0)
    {
        normal = -intersection->_normal;
    }
    else 
    {
        normal = intersection->_normal;
    }
    
    double lightxnormal = dot_product(normal, light_direction);

    color3 diffuse_component = source_light * material._object_color * material._diffuse * lightxnormal;


    double norm_factor = (material._shinyness + 2) / (2 * M_PI);
    norm_factor = 1 / M_PI;
    vector3 reflection_direction = unit_vector((2 * dot_product(light_direction, normal) * normal) - light_direction);
    double reflectionxray = dot_product(reflection_direction, -raymond.direction());
    if (reflectionxray < 0) { reflectionxray = 0; }
    color3 specular_component = source_light * norm_factor 
        * material._specular 
        * pow(reflectionxray, material._shinyness);
    
    color3 light_color = ambiente_component + diffuse_component + specular_component;

    return light_color;
}


image_data* trace_rays()
{   
    //possible parameters
    double focal_length = 1.0;
    double viewport_ratio = 200;
    double aspect_ratio = 16.0 / 9.0;
    int image_width = 600;
    point3 camera_center = point3(0, 0, 0);

    //light
    point3 light_source = vector3(3, 0, 1);


    int image_height = (int)(image_width / aspect_ratio);


    double viewport_width = image_width / viewport_ratio;
    double viewport_height = image_height / viewport_ratio;

    //pixel vectors
    vector3 viewport_delta_x = vector3(viewport_width/image_width, 0, 0);
    vector3 viewport_delta_y = vector3(0, -viewport_height / image_height, 0);

    //assume the viewport is in positive z direction
    point3 start_point = camera_center - vector3(0, 0, focal_length) - viewport_delta_x * (image_width / 2.0 - 0.5) - viewport_delta_y * (image_height / 2.0 - 0.5);
    
    unsigned char* image_pixels = new unsigned char[(size_t)(image_width * image_height * 3)];



    std::vector<triangle3>* triangles;
    size_t triangles_size;
    std::tie(triangles, triangles_size) = get_triangles();

    for (int y = 0; y < image_height; y++)
    {
        for (int x = 0; x < image_width; x++)
        {
            point3 pixel_point = start_point + (x * viewport_delta_x) + (y * viewport_delta_y);
            vector3 ray_direction = unit_vector(pixel_point - camera_center);
            ray raymond(camera_center, ray_direction);

            
            // background color
            vector3 unit_direction = raymond.direction();
            double a = 0.5 * (unit_direction.y() + 1.0);
            color3 pixel_color = (1.0 - a) * color3(1.0, 1.0, 1.0) + a * color3(0.5, 0.7, 1.0);

            //The intersection tests
            Intersection* closest_intersection = get_closest_intersection(focal_length, pixel_point, triangles_size,
                triangles, raymond);

            // change the pixel_color to red if an intersection occured
            if (closest_intersection != NULL)
            {
                pixel_color = calculate_light(triangles_size, triangles, closest_intersection, light_source, raymond);
            }
            delete closest_intersection;
            image_pixels[3 * (y * image_width + x)] = unsigned char(pixel_color.x() * 255.999);
            image_pixels[3 * (y * image_width + x) + 1] = unsigned char(pixel_color.y() * 255.999);
            image_pixels[3 * (y * image_width + x) + 2] = unsigned char(pixel_color.z() * 255.999);
        }
    }
    image_data* img = new image_data(image_width, image_height, 3, image_pixels);
    return img;
}
