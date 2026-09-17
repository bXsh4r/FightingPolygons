#include "draw.h"

#include <SDL3/SDL.h>
#include <stdio.h>

#define WIDTH 320
#define HEIGHT 200

uint32_t framebuffer[WIDTH * HEIGHT];

int create_window(){

	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Texture *texture;

	SDL_Event event;

	if(!SDL_Init(SDL_INIT_VIDEO)){
		fprintf(stderr, "SDL Init failed: %s \n", SDL_GetError());
		return 1;
	}	

	window = SDL_CreateWindow(
		"SDL Framebuffer",
		WIDTH * 4,
		HEIGHT * 4,
		0
	);

	if(window == NULL) {
		fprintf(stderr, "SDL_CreateWindow failed: %s \n", SDL_GetError());
		SDL_Quit();
		return 1; 
	}

	renderer = SDL_CreateRenderer(
		window,
		NULL
	);

	if(renderer == NULL) {

		fprintf(stderr, "SDL_CreateRenderer failed: %s \n", SDL_GetError());
		SDL_DestroyWindow(window);
		SDL_Quit();
		return 1;
	 }

	texture = SDL_CreateTexture(
		renderer,
		SDL_PIXELFORMAT_XRGB8888,
		SDL_TEXTUREACCESS_STREAMING,
		WIDTH,
		HEIGHT
	);
	
	if(texture == NULL) {
		fprintf(stderr, "SDL_CreateTexture failed: %s \n", SDL_GetError());
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
		return 1;
	}

	SDL_SetTextureScaleMode(texture, SDL_SCALEMODE_NEAREST); // copy the original pixel to make new pixels which results in a bigger sharp pixel

	uint8_t isRunning = true;
	
	while(isRunning) {
		
		while(SDL_PollEvent(&event)){
			if(event.type == SDL_EVENT_QUIT){
				isRunning = false;
			}
		}
		

		SDL_UpdateTexture(
			texture,
			NULL,
			framebuffer,
			WIDTH * sizeof(uint32_t)
		);
			
		SDL_RenderClear(renderer);
		SDL_RenderTexture(renderer, texture, NULL, NULL);
		SDL_RenderPresent(renderer);
	}

	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	
	SDL_Quit();
}


int main() {

	
	draw_init(framebuffer, WIDTH, HEIGHT);
	
	/*
		draw functions go here
	*/


	if(create_window() == 1) {
		return 1;
	}
	return 0;
}
