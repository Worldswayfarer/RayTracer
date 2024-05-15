#include "raytracer.h"


vector3 ray_color(const ray& r) {
    vector3 unit_direction = unit_vector(r.direction());
    auto a = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - a) * vector3(1.0, 1.0, 1.0) + a * vector3(0.5, 0.7, 1.0);
}


image_data* trace_rays()
{   
    //possible parameters
    float focal_length = 1.0;
    float viewport_ratio = 200;
    float aspect_ratio = 16.0 / 9.0;
    int image_width = 400;
    point3 camera_center = point3(0, 0, 0);

    int image_height = (int)image_width / aspect_ratio;


    float viewport_width = image_width / viewport_ratio;
    float viewport_height = image_height / viewport_ratio;

    //pixel vectors
    vector3 viewport_delta_x = vector3(viewport_width/image_width, 0, 0);
    vector3 viewport_delta_y = vector3(0, -viewport_height / image_height, 0);

    //assume the viewport is in positive z direction
    point3 start_point = camera_center + vector3(0, 0, focal_length) - viewport_delta_x * (image_width/2 - 0.5) - viewport_delta_y * (image_height / 2 - 0.5);
    
    unsigned char* image_pixels = new unsigned char[(double)image_width * image_height * 3];

    for (int y = 0; y < image_height; y++)
    {
        for (int x = 0; x < image_width; x++)
        {
            point3 pixel_point = start_point + (x * viewport_delta_x) + (y * viewport_delta_y);
            vector3 ray_direction = pixel_point - camera_center;
            ray raymond(camera_center, ray_direction);
            vector3 color = ray_color(raymond);
            image_pixels[3 * (y * image_width + x)] = unsigned char(color.x() * 255.999);
            image_pixels[3 * (y * image_width + x) + 1] = unsigned char(color.y() * 255.999);
            image_pixels[3 * (y * image_width + x) + 2] = unsigned char(color.z() * 255.999);
        }
    }
    struct image_data img(image_width, image_height, 3, image_pixels);
    return &img;
}
