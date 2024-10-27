#include "image_data.h"
#include <stdlib.h>

image_data* create_image()
{

    const int image_width = 1920;
    const int image_height = 1080;
    
    unsigned char* image_pixels = new unsigned char[(size_t)(image_width * image_height * 3)];
    

    for (int y = 0; y < image_height; y++) {
        for (int x = 0; x < image_width; x++) {
            /*Red*/
            double red = double(x) / (image_width - 1);
            image_pixels[3 * (y * image_width + x)] = unsigned char(red * 255.999);
            /*Green*/
            double green = double(y) / (image_height - 1);
            image_pixels[3 * (y * image_width + x) + 1] = unsigned char(green * 255.999);
            /*Blue*/
            double blue = 5;
            image_pixels[3 * (y * image_width + x) + 2] = unsigned char(blue * 255.999);

        }
    }

    struct image_data* img = new image_data(image_width, image_height, 3, image_pixels);
    return img;
}