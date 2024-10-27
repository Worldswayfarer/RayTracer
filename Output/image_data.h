#pragma once

struct image_data 
{
	const int image_width;
	const int image_height;
	const int image_channels;
	unsigned char* image_pixels;

	image_data(int image_width, int image_height, int image_buffer, unsigned char* image_pixels)
		: image_width(image_width), image_height(image_height), image_channels(image_buffer), image_pixels(image_pixels)
	{
	}
	~image_data()
	{
	}
};