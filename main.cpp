#include "image.h"
#include "printer.h"
#include "image_data.h"
#include "window.h"
#undef main

int main()
{
	image_data* img = create_image();
	print_image(img);


	//displaying an image is currently not working
	//sdl_window(img);
	return 0;
}