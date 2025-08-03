//#include <SDL2/SDL_keyboard.h>
//#include <SDL2/SDL_events.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include "chip8.h"


SDL_KeyboardEvent key;

void init_keyboard(SDL_Window *window){
	key.windowID = SDL_GetWindowID(window);
}

