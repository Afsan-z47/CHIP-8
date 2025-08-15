#ifndef __AUDIO__
#define __AUDIO__

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

int init_audio(Mix_Chunk **beep, char* audio_file);
	
#endif
