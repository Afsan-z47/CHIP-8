#include <SDL2/SDL.h>
#include "display.h"

#define VIDEO_WIDTH 64
#define VIDEO_HEIGHT 32
#define SCALE 25


SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

void init_Graphics() {
	SDL_Init(SDL_INIT_VIDEO);

	window = SDL_CreateWindow("CHIP-8 Emulator",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		VIDEO_WIDTH * SCALE, VIDEO_HEIGHT * SCALE, SDL_WINDOW_SHOWN);
	
	

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if (!window || !renderer) {
		fprintf(stderr, "SDL Error: %s\n", SDL_GetError());
		exit(1);
	}
}
/*
void draw_Graphics(CHIP_8 *chip) {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black background
	SDL_RenderClear(renderer);

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White pixels

	for (int y = 0; y < 32; ++y) {
		for (int x = 0; x < 64; ++x) {
			if (chip->DISPLAY[x + y * 64]) {
				SDL_Rect pixel = { x * SCALE, y * SCALE, SCALE, SCALE };
				SDL_RenderFillRect(renderer, &pixel);
			}
		}
	}

	SDL_RenderPresent(renderer);
	chip->DRAW_FLAG = 0;
}
*/

void draw_Graphics(CHIP_8 *chip) {
	SDL_SetRenderDrawColor(renderer, 10, 20, 10, 255);  // Dark green background
	SDL_RenderClear(renderer);

	SDL_SetRenderDrawColor(renderer, 153, 255, 153, 255); // Green pixels
	for (int y = 0; y < 32; y++) {
		for (int x = 0; x < 64; x++) {
			if (chip->DISPLAY[y * 64 + x]) {
				SDL_Rect pixel = { x * SCALE, y * SCALE, SCALE, SCALE };
				SDL_RenderFillRect(renderer, &pixel);
			}
		}
	}
	SDL_RenderPresent(renderer);
}

