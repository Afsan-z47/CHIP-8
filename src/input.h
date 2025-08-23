#ifndef __INPUT__
#define __INPUT__
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_video.h>
#include "chip8.h"
#include "display.h"
int key_input(SDL_Event EVENT, CHIP_8 *chip);
#endif
