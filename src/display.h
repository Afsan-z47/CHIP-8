#ifndef __DISPLAY__
#define __DISPLAY__
#include "chip8.h"
#include <SDL2/SDL.h>

extern SDL_Window *window;
extern SDL_Renderer *renderer;

void init_Graphics();
void draw_Graphics(CHIP_8 *chip);
#endif
