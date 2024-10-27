

#include "Output/image.h"
#include "Output/printer.h"
#include "window.h"
#include "raytracer.h"
#undef main



int main()
{
	image_data* img = trace_rays();
	print_image(img);


	//displaying an image is currently not working
	//sdl_window(img);
	return 0;
}