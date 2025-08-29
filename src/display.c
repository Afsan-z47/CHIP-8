#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include "display.h"

#define VIDEO_WIDTH 64
#define VIDEO_HEIGHT 32
#define SCALE 25

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
SDL_Texture *texture = NULL;

// RGBA pixel buffer for the texture
static uint32_t pixels[VIDEO_WIDTH * VIDEO_HEIGHT];

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

	// Create a streaming texture for the 64x32 framebuffer
	texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, VIDEO_WIDTH, VIDEO_HEIGHT);

	//Check for creation ERRORs
	if (!window || !renderer || !texture) {
		fprintf(stderr, "SDL Error: %s\n", SDL_GetError());
		exit(1);
	}


	// Optional: nearest-neighbor scaling for crisp pixels
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest");


}


void draw_Graphics(CHIP_8 *chip) {

	//NOTE: Scaling is calculated here
	// Get current window
	int height;
	int width;
	SDL_GetRendererOutputSize(renderer, &width, &height);
	int scale_X = width / VIDEO_WIDTH;
	int scale_Y = height / VIDEO_HEIGHT;
	int scale = (scale_X < scale_Y) ? scale_X : scale_Y;

	
	// Pixel Position (x,y) then pixel size (width, height)
	// NOTE: Pixels are scalling equally for using "scale" on both width and height
	SDL_Rect pixel = { 
		(width - VIDEO_WIDTH * scale) / 2,
		(height - VIDEO_HEIGHT * scale) / 2,
		VIDEO_WIDTH * scale,
		VIDEO_HEIGHT * scale
	};

	// Update texture with pixel buffer
    	SDL_UpdateTexture(texture, NULL, chip->DISPLAY, VIDEO_WIDTH * sizeof(unsigned int));

	// Update the whole screen with renderer as argument according to the set color by SDL_SetRenderDrawColor
	SDL_RenderClear(renderer); 


	// Sets the renderer area
	// NOTE: window, pixel locations and renderer aligns by using the same scaling
	//SDL_RenderSetLogicalSize(renderer, VIDEO_WIDTH * scale , VIDEO_HEIGHT * scale);

	SDL_RenderCopy(renderer, texture, NULL, &pixel);
	SDL_RenderPresent(renderer); //Update Screen

	//FIXME: OH! HERE!
	chip->DRAW_FLAG = 0;
}

/*
void draw_Graphics(CHIP_8 *chip) {

	// Convert DISPLAY to pixel array
	for (int y = 0; y < VIDEO_HEIGHT; y++) {
		for (int x = 0; x < VIDEO_WIDTH; x++) {
			uint32_t color = chip->DISPLAY[x + y * VIDEO_WIDTH] ? 0xFF99FF99 : 0xFF0A140A; // ON = green, OFF = dark green
			pixels[x + y * VIDEO_WIDTH] = color;
		}
	}

	// Update texture with pixel buffer
	SDL_UpdateTexture(texture, NULL, pixels, VIDEO_WIDTH * sizeof(uint32_t));

	// Clear screen (background color is ignored because texture covers everything)
	SDL_RenderClear(renderer);

	// Determine window size and compute integer scale for aspect ratio
	int win_width, win_height;
	SDL_GetRendererOutputSize(renderer, &win_width, &win_height);

	int scaleX = win_width / VIDEO_WIDTH;
	int scaleY = win_height / VIDEO_HEIGHT;
	int scale = (scaleX < scaleY) ? scaleX : scaleY;

	// Compute destination rect for scaled texture
	SDL_Rect dstRect = {
		.x = (win_width - VIDEO_WIDTH * scale) / 2,
		.y = (win_height - VIDEO_HEIGHT * scale) / 2,
		.w = VIDEO_WIDTH * scale,
		.h = VIDEO_HEIGHT * scale
	};

	SDL_RenderCopy(renderer, texture, NULL, &dstRect);
	SDL_RenderPresent(renderer);

	chip->DRAW_FLAG = 0;
}
*/
/*
	FIXME:THESE DID NOT WORK! I wonder why?

	// 🔑 Enforce integer scaling so each CHIP-8 pixel stays square
	//SDL_RenderSetIntegerScale(renderer, SDL_TRUE);

	// Optional: nearest-neighbor scaling for crisp pixels
	//SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest");
*/
