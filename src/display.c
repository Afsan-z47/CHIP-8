#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include "display.h"

#define VIDEO_WIDTH 64
#define VIDEO_HEIGHT 32
#define SCALE 25

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

void init_Graphics() {

	// SDL_CreateWindow(TITLE, Position X, Position Y, Window Width, Window Height, Windoe Flag);
	//	The window flag is part of a bit mask. Can be combined using the "|" operator.
	//	SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI
	//	SDL_WINDOW_SHOWN for showing the window

	window = SDL_CreateWindow("CHIP-8 Emulator",
			   SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			   VIDEO_WIDTH * SCALE , VIDEO_HEIGHT * SCALE, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	
	// Setting minumux window size
	SDL_SetWindowMinimumSize(window, VIDEO_WIDTH * 5, VIDEO_HEIGHT * 5);


	// SDL_RENDERER_ACCELERATED for Hardware Acceleration using GPU
	//FIXME: Direct leaks were traced to this function call
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	
	//Check for creation ERRORs
	if (!window || !renderer) {
		fprintf(stderr, "SDL Error: %s\n", SDL_GetError());
		exit(1);
	}
}
void draw_Graphics(CHIP_8 *chip) {

	// Get current window
	int height;
	int width;
	SDL_GetRendererOutputSize(renderer, &width, &height);
	int scale_X = width / VIDEO_WIDTH;
	int scale_Y = height / VIDEO_HEIGHT;
	int scale = (scale_X < scale_Y) ? scale_X : scale_Y;

	// Sets the Color to be drawn in renderer 
	// Renderer, R, G, B, A -> RED, GREEN, BLUE, ALPHA
	SDL_SetRenderDrawColor(renderer, 10, 20, 10, 255);  // Dark green background
	//SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black background

	// Update the whole screen with renderer as argument according to the set color by SDL_SetRenderDrawColor
	SDL_RenderClear(renderer); 

	SDL_SetRenderDrawColor(renderer, 153, 255, 153, 255); // Green pixels
	//SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White pixels

	for (int y = 0; y < VIDEO_HEIGHT; y++) {
		for (int x = 0; x < VIDEO_WIDTH; x++) {
			if (chip->DISPLAY[y * VIDEO_WIDTH + x]) {

				// Pixel Position (x,y) then pixel size (width, height)
				// NOTE: Pixels are scalling equally for using "scale" on both width and height
				SDL_Rect pixel = { 
					x * scale,
					y * scale,
					scale,
					scale
				};

				//FILLS the rectangle defined by SDL_Rect with the color set by SDL_SetRendererDrawColor in renderer
				SDL_RenderFillRect(renderer, &pixel);
			}
		}
	}
	//FIXME: OH! HERE!
	chip->DRAW_FLAG = 0;
	// Sets the renderer area
	// NOTE: window, pixel locations and renderer aligns by using the same scaling
	SDL_RenderSetLogicalSize(renderer, VIDEO_WIDTH * scale , VIDEO_HEIGHT * scale);
	
	SDL_RenderPresent(renderer); //Update Screen
}


/*
	FIXME:THESE DID NOT WORK! I wonder why?
	
	// 🔑 Enforce integer scaling so each CHIP-8 pixel stays square
	//SDL_RenderSetIntegerScale(renderer, SDL_TRUE);

	// Optional: nearest-neighbor scaling for crisp pixels
	//SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest");
*/
