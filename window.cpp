#pragma once
#include "Output/image_data.h"
#include <SDL.h>
#include <stdio.h>


int sdl_window(image_data *img)
{	
	int width = (*img).image_width;
	int height = (*img).image_height;

    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* window = SDL_CreateWindow("RayTracer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
    SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    
	SDL_Surface* tempSurface = SDL_CreateRGBSurface(0, width, height, 24, 0, 0, 0, 0);
	if (tempSurface == nullptr)
	{
		printf((char*)SDL_GetError);
		return 1;
	}
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
	//SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB888, SDL_TEXTUREACCESS_TARGET, width, height);

	
	SDL_QueryTexture(texture, NULL, NULL, &width, &height);
		
	SDL_UpdateTexture(texture, NULL, (*img).image_pixels, width * sizeof(unsigned char));


	// Copy the texture to the renderer.
	SDL_Rect srcRect, bounds;
	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = width;
	srcRect.h = height;
	bounds = srcRect;

	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, texture, &srcRect, &bounds);

    SDL_RenderPresent(renderer);

    SDL_Delay(3000);

	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

    return 0;
}