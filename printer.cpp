#include "printer.h"
#include "image_data.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

int print_image(struct image_data* img)
{
    stbi_write_png("image2.png", (*img).image_width, (*img).image_height, 3, (*img).image_pixels, (*img).image_width * 3);
    return 0;
}
