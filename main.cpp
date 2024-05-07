#include "image.h"
#include "printer.h"
#include "image_data.h"
#undef main

int main()
{
	struct image_data * img = create_image();
	print_image(img);
	return 0;
}