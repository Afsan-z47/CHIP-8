#ifndef __DISPLAY__
#define __DISPLAY__
#include "chip8.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>

extern SDL_Window *window;
extern SDL_Renderer *renderer;
extern SDL_Texture *texture;

void init_Graphics();
void draw_Graphics(CHIP_8 *chip);
#endif
