#include "image_data.h"
#include <stdlib.h>

image_data create_image()
{

    const int image_width = 256;
    const int image_height = 256;
    
    unsigned char* image_pixels = (unsigned char*)malloc((double)image_width * image_height * 3 * sizeof(unsigned char));
    

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

    struct image_data img(image_width, image_height, 3, image_pixels);
    return img;
}