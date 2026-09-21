#include "vertex.h"
#include "draw.h"
#include "transformation2d.h"

#include <SDL3/SDL.h>
#include <stdio.h>

#define WIDTH 320*4
#define HEIGHT 200*4

uint32_t framebuffer[WIDTH * HEIGHT];


void update_screen(float value) {
	
	Vertex vertices[] = {{200, 600, 0x0000FF}, {280, 440, 0xFF0000}, {360, 640, 0x00FF00}};
	
	Matrix rotate = rotation_matrix(value);
	transform(vertices, 3, &rotate);	

	for(int i=0; i<3; i++) {
		printf("index: %d, new x: %.2f, new y: %.2f\n", i, vertices[i].x, vertices[i].y);
	}		
	draw_tri(vertices[0], vertices[1], vertices[2], true);
}


int create_window(){

	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Texture *texture;

	SDL_Event event;

	const double target_frame = 1.0 / 60.0;

	if(!SDL_Init(SDL_INIT_VIDEO)){
		fprintf(stderr, "SDL Init failed: %s \n", SDL_GetError());
		return 1;
	}	

	window = SDL_CreateWindow(
		"SDL Framebuffer",
		WIDTH,
		HEIGHT,
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
	float value = 0.0f;
	while(isRunning) {

		uint64_t start = SDL_GetPerformanceCounter();
		
		while(SDL_PollEvent(&event)){
			if(event.type == SDL_EVENT_QUIT){
				isRunning = false;
			}
		}

		
		memset(framebuffer, 0, sizeof(int) * WIDTH * HEIGHT);	
	//	value %= (320 * 4); // extremely important limits the value from getting bigger than the width (it will still be bigger because its "x + value" but still small enough to not cause any overflow)
		update_screen(value);


		SDL_UpdateTexture(
			texture,
			NULL,
			framebuffer,
			WIDTH * sizeof(uint32_t)
		);
			
		SDL_RenderClear(renderer);
		SDL_RenderTexture(renderer, texture, NULL, NULL);
		SDL_RenderPresent(renderer);

		uint64_t end = SDL_GetPerformanceCounter();

		double elapsed = (double)(end - start) / (double)SDL_GetPerformanceFrequency();

		if(elapsed < target_frame) {
			SDL_Delay((target_frame - elapsed) * 1000);
		}

		value += 0.5f;
	}

	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	
	SDL_Quit();
}



int main(void) {

	draw_init(framebuffer, WIDTH, HEIGHT);

	if(create_window() == 1) 
		return 1;
	return 0;
}
