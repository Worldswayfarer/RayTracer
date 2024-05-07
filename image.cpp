

#include "image_data.h"


image_data* create_image()
{

    // Image

    const int image_width = 256;
    const int image_height = 256;

    // Render

    char image_data[image_width * image_height * 3] = {};
    

    for (int y = 0; y < image_height; y++) {
 
        for (int x = 0; x < image_width; x++) {
            /*Red*/
            auto red = double(x) / (image_width - 1);
            image_data[3 * (y * image_width + x)] = unsigned char(red * 255.999);
            /*Green*/
            auto green = double(y) / (image_height - 1);
            image_data[3 * (y * image_width + x) + 1] = unsigned char(green * 255.999);
            /*Blue*/
            auto blue = red + green;
            image_data[3 * (y * image_width + x) + 2] = unsigned char(blue * 255.999);

        }
    }

    struct image_data img(image_width, image_height, 3, image_data);
    return &img;
}