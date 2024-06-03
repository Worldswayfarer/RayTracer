#include "raytracer.h"
#include "triangle3.h"
#include <tuple>

double ray_sphere_intersetion(const point3& center, double radius, const ray& raymond) 
{
    vector3 oc = center - raymond.origin();
    double a = dot_product(raymond.direction(), raymond.direction());
    double b = -2.0 * dot_product(raymond.direction(), oc);
    double c = dot_product(oc, oc) - radius * radius;
    double discriminant = b * b - 4 * a * c;

    if (discriminant < 0) {
        return -1.0;
    }
    return (-b + sqrt(discriminant)) / (2.0 * a);
}


vector3 ray_color(const ray& raymond) 
{   
    double t = ray_sphere_intersetion(point3(0, 0, -1), 0.5, raymond);
    if (t > 0.0) {
        vector3 N = unit_vector(raymond.at(t) - vector3(0, 0, -1));
        return 0.5 * color3(N.x() + 1, N.y() + 1, N.z() + 1);
    }

    vector3 unit_direction = unit_vector(raymond.direction());
    double a = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - a) * color3(1.0, 1.0, 1.0) + a * color3(0.5, 0.7, 1.0);
}


std::tuple<triangle3*, int> get_triangles()
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
    triangles[8] = triangle3(left_front, right_front, left_back);
    triangles[9] = triangle3(left_front, right_front, right_back);
    //bottom
    triangles[10] = triangle3(left_down_front, right_down_front, left_down_back);
    triangles[11] = triangle3(left_down_front, right_down_front, right_down_back);


    return std::make_tuple(triangles, triangle_count);
}


image_data* trace_rays()
{   
    //possible parameters
    double focal_length = 1.0;
    double viewport_ratio = 200;
    double aspect_ratio = 16.0 / 9.0;
    int image_width = 600;
    point3 camera_center = point3(0, 0, 0);

    int image_height = (int)(image_width / aspect_ratio);


    double viewport_width = image_width / viewport_ratio;
    double viewport_height = image_height / viewport_ratio;

    //pixel vectors
    vector3 viewport_delta_x = vector3(viewport_width/image_width, 0, 0);
    vector3 viewport_delta_y = vector3(0, -viewport_height / image_height, 0);

    //assume the viewport is in positive z direction
    point3 start_point = camera_center - vector3(0, 0, focal_length) - viewport_delta_x * (image_width / 2.0 - 0.5) - viewport_delta_y * (image_height / 2.0 - 0.5);
    
    unsigned char* image_pixels = new unsigned char[(size_t)(image_width * image_height * 3)];


    triangle3* triangles;
    size_t triangles_size;
    std::tie(triangles, triangles_size) = get_triangles();

    for (int y = 0; y < image_height; y++)
    {
        for (int x = 0; x < image_width; x++)
        {
            point3 pixel_point = start_point + (x * viewport_delta_x) + (y * viewport_delta_y);
            vector3 ray_direction = pixel_point - camera_center;
            ray raymond(camera_center, ray_direction);

            
            vector3 unit_direction = unit_vector(raymond.direction());
            double a = 0.5 * (unit_direction.y() + 1.0);
            color3 pixel_color = (1.0 - a) * color3(1.0, 1.0, 1.0) + a * color3(0.5, 0.7, 1.0);

            point3* closest_intersection_point = NULL;

            for (int n = 0; n < triangles_size; n++)
            {
                double ray_t = triangles[n].ray_triangle_intersection(raymond);
                if (ray_t < 0) { continue; }

                vector3 distance_ray_point = raymond.direction() * ray_t;
                // intersection is behind the image
                if (distance_ray_point.length() < focal_length) { continue; }

                point3 possible_intersection(raymond.origin() + distance_ray_point);
                if (closest_intersection_point == NULL)
                {
                    closest_intersection_point = &possible_intersection;
                    continue;
                }

                //determine which of the 2 points is closer to the image
                if ((possible_intersection - pixel_point).length() < (*closest_intersection_point - pixel_point).length())
                {
                    closest_intersection_point = &possible_intersection;
                }
            }

            // change the pixel_color to red if an intersection occured
            if (closest_intersection_point != NULL)
            {
                pixel_color = color3(1, 0, 0);
            }
            
            image_pixels[3 * (y * image_width + x)] = unsigned char(pixel_color.x() * 255.999);
            image_pixels[3 * (y * image_width + x) + 1] = unsigned char(pixel_color.y() * 255.999);
            image_pixels[3 * (y * image_width + x) + 2] = unsigned char(pixel_color.z() * 255.999);
        }
    }
    struct image_data img(image_width, image_height, 3, image_pixels);
    return &img;
}