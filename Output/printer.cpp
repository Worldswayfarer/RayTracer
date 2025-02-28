#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include "image_data.h"



int print_image(image_data* img)
{
    stbi_write_png("Output/image.png", (*img).image_width, (*img).image_height, (*img).image_channels, (*img).image_pixels->data(), (*img).image_width * (*img).image_channels);
    return 0;
}
