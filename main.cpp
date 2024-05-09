#include "image.h"
#include "printer.h"
#include "image_data.h"
#include "window.h"
#undef main

int main()
{
	
	print_image(create_image());
	//sdl_window(img);
	return 0;
}