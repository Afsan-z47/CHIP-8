#include "display.h"
#include <SDL2/SDL_render.h>

#define VIDEO_WIDTH 64
#define VIDEO_HEIGHT 32
#define SCALE 25

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
SDL_Texture *texture = NULL;

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

	//GPU Based Rendering
	//NOTE: SDL_RENDERER_PRESETVSYNC makes SDL_RenderPresent() wait for the monitor refresh before swapping buffers, to prevent tearing and cap frame rate.
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!renderer ) {
		fprintf(stderr, "GPU rendering failed. Falling back to CPU. SDL ERROR: %s\n", SDL_GetError());
		//CPU Based Rendering
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE | SDL_RENDERER_PRESENTVSYNC);
		if (!renderer ) {
			fprintf(stderr, "CPU rendering failed. Closing. SDL ERROR: %s\n", SDL_GetError());
			exit(1); //FIXME:
		}
	}
	// Create a streaming texture for the 64x32 framebuffer
	texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, VIDEO_WIDTH, VIDEO_HEIGHT);

	//Check for creation ERRORs
	if (!window || !renderer || !texture) {
		fprintf(stderr, "SDL Error: %s\n", SDL_GetError());
		exit(1); //FIXME:
	}

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


	// Define the destination rectangle on the window where the texture will be drawn
	// SDL_Rect: {x, y, width, height}
	// - x, y: top-left corner of where the texture starts
	// - width, height: size to scale the texture to
	// NOTE: Pixels are scaled uniformly using 'scale' so each CHIP-8 pixel stays square
	//       and the display is centered in the window.
	SDL_Rect pixel = { 
		(width - VIDEO_WIDTH * scale) / 2,   // center horizontally
		(height - VIDEO_HEIGHT * scale) / 2, // center vertically
		VIDEO_WIDTH * scale,                  // scale width of the texture
		VIDEO_HEIGHT * scale                  // scale height of the texture
	};

	//NOTE: SDL_UpdateTexture(SDL_Texture *texture, const SDL_Rect *rect, const void *pixels, int pitch);
	// - Upload the CHIP-8 framebuffer (chip->DISPLAY) to the SDL texture
	// - NULL  -> as second argument means we update the entire texture
	// - pitch -> The number of bytes per row: VIDEO_WIDTH * sizeof(unsigned int)
	//FIXME: Minimize texture update avoiding NULL as 2nd perameter
	SDL_UpdateTexture(texture, NULL, chip->DISPLAY, VIDEO_WIDTH * sizeof(unsigned int));

	// Clear the current rendering target (window) with the current draw color
	//NOTE: It's not required for the renderer but ensured EXTRA window area remains default
	SDL_RenderClear(renderer); 

	//NOTE: SDL_RenderCopy(SDL_Renderer *renderer, SDL_Texture *texture, const SDL_Rect *srcrect, const SDL_Rect *dstrect)
	// - Copy the texture to the rendering target (window) at the destination rectangle
	// - SDL_Rect *srcrect -> NULL : Use all the pixel at the texture as source
	// - SDL_RECT *dstrect -> &pixel: destination rectangle on the window (scaled and centered)
	// It maps pixels from the source rectangle (srcrect) in the texture to pixels in the destination rectangle (dstrect) on the renderer.
	// Every pixel in srcrect gets stretched or compressed to fit into dstrect.
	// Mapping is linear: source (x, y) → destination (x', y').
	SDL_RenderCopy(renderer, texture, NULL, &pixel);

	// Present the updated renderer to the window
	// This actually draws everything to the screen

	SDL_RenderPresent(renderer);
	//FIXME: OH! HERE!
	chip->DRAW_FLAG = 0;
}
//FIXME: What does this do?
// Optional: nearest-neighbor scaling for crisp pixels
//SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest");

