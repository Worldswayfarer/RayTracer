#pragma once
#include "raytracer.h"
#include "Data/triangle3.h"
#include "Data/sphere.h"
#include "Data/RGB_Material.h"
#include "BVH/Construct_BVH.h"
#include <tuple>
#include <ctime>
#include <chrono>
#include <iostream>

#include <algorithm>
#include <cmath>
#include "Scene/example_scene.h"
#include "Intersection.h"
#include "closest_intersection.h"
#include <vector>
#include "ObjectLoader/loader.h"

const bool useBVH = true;
const bool useLoader = false;

std::tuple<std::vector<triangle3>*, int> get_triangles()
{
    return build_scene(10);
}


// Using Phong
color3 calculate_light(BVHNode* boundingVolumeHierarchy, size_t triangles_size, std::vector<triangle3>* triangles, Intersection* intersection, point3 light_source, ray raymond)
{
    RGB_Material material = intersection->_material;

    color3 source_light(1, 1, 1);
    color3 light_ambiente(0.15, 0.15, 0.15);

    color3 ambiente_component = light_ambiente * material._ambiente * material._object_color;
  
    vector3 normal;

    //points towards the lightsource
    vector3 light_direction = unit_vector(light_source - intersection->_intersection_point);
    ray shadow_ray = ray(intersection->_intersection_point, light_direction);
    double distance_to_light_source = (light_source - intersection->_intersection_point).length();
    
    Intersection* shadow_intersection = nullptr;

    if (useBVH) {
        shadow_intersection = get_BVH_closest_intersection(boundingVolumeHierarchy, shadow_ray);
    }
    else
    {
        shadow_intersection = get_closest_intersection(triangles_size, triangles, shadow_ray);
    }
    if (shadow_intersection != nullptr and shadow_intersection->_ray_t < distance_to_light_source )
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
    if(useLoader)
    {
        viewport_ratio *= 50;
    }
    double aspect_ratio = 16.0 / 9.0;
    int image_width = 1920;
    point3 camera_center = point3(0, 0, 2);

    //light
    point3 light_source = vector3(5, 5, 0);
    sphere light_object(light_source, 0.05);


    int image_height = (int)(image_width / aspect_ratio);


    double viewport_width = image_width / viewport_ratio;
    double viewport_height = image_height / viewport_ratio;

    //pixel vectors
    vector3 viewport_delta_x = vector3(viewport_width/image_width, 0, 0);
    vector3 viewport_delta_y = vector3(0, -viewport_height / image_height, 0);

    //assume the viewport is in negative z direction
    point3 start_point = camera_center - vector3(0, 0, focal_length) - viewport_delta_x * (image_width / 2.0 - 0.5) - viewport_delta_y * (image_height / 2.0 - 0.5);
    
    size_t image_size = (size_t)(image_width * image_height * 3);

    std::vector<unsigned char>* image_pixels = new std::vector<unsigned char>(image_size, 0);
    //Getting triangles
    auto start = std::chrono::system_clock::now();
    
    std::vector<triangle3>* triangles = new std::vector<triangle3>();
    std::string obj_path = "C:/Users/Kenny/source/repos/RayTracer/ObjectLoader/stanford-bunny.obj";
    size_t triangles_size;
    if (useLoader) {
        const bool success = simple_loadOBJ(obj_path, triangles);
        if (success)
        {
            triangles_size = triangles->size();
        }
        else {
            exit(1);
        }
        
    }
    else {
        std::tie(triangles, triangles_size) = get_triangles();
    }
    std::vector<triangle3>* plane;
    size_t plane_size = 0;
    std::tie(plane, plane_size) = build_plane(point3(0, -6, -50), 100);
    if (plane)
    {
        triangles->insert(triangles->end(), plane->begin(), plane->end());
        triangles_size += plane_size;
    }
    
    BVHNode* boundingVolumeHierarchy = construct_BVH(triangles);

    auto end = std::chrono::system_clock::now();

    std::chrono::duration<double> elapsed_seconds = end - start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);

    std::cout << "Building scene: " << elapsed_seconds.count() << "s"
        << std::endl;

    start = std::chrono::system_clock::now();
    Intersection* closest_intersection = NULL;


    for (int y = 0; y < image_height; y++)
    {
        for (int x = 0; x < image_width; x++)
        {
            point3 pixel_point = start_point + (x * viewport_delta_x) + (y * viewport_delta_y);
            vector3 ray_direction = unit_vector(pixel_point - camera_center);
            ray raymond(pixel_point, ray_direction);

            
            // background color
            vector3 unit_direction = raymond.direction();
            double a = 0.5 * (unit_direction.y() + 1.0);
            color3 pixel_color = (1.0 - a) * color3(1.0, 1.0, 1.0) + a * color3(0.5, 0.7, 1.0);

            //The intersection tests
            closest_intersection = NULL;
            if (useBVH) {
                closest_intersection = get_BVH_closest_intersection(boundingVolumeHierarchy, raymond);
            }
            else {
                closest_intersection = get_closest_intersection(triangles_size,
                    triangles, raymond);
            }

 
            // change the pixel_color to red if an intersection occured
            if (closest_intersection != NULL)
            {
                pixel_color = calculate_light(boundingVolumeHierarchy, triangles_size, triangles, closest_intersection, light_source, raymond);
            }
            
            float sphere_t = light_object.ray_sphere_intersetion(raymond);
            if (sphere_t > 0)
            {
                if (closest_intersection and closest_intersection->_ray_t > sphere_t)
                {
                    pixel_color = color3(1, 0, 0);
                }
                else {
                    pixel_color = color3(1, 0, 0);
                }
                
            }
            
            
            image_pixels->at(3 * (y * image_width + x)) = unsigned char(pixel_color.x() * 255.999);
            image_pixels->at(3 * (y * image_width + x) + 1) = unsigned char(pixel_color.y() * 255.999);
            image_pixels->at(3 * (y * image_width + x) + 2) = unsigned char(pixel_color.z() * 255.999);
        }
    }
    image_data* img = new image_data(image_width, image_height, 3, image_pixels);


    end = std::chrono::system_clock::now();

    elapsed_seconds = end - start;
    end_time = std::chrono::system_clock::to_time_t(end);

    std::cout << "Rendering scene: " << elapsed_seconds.count() << "s"
        << std::endl;

    return img;
}
