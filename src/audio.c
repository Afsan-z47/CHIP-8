#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>

void init_audio(Mix_Chunk **beep, char* audio_file){
	if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
	{
		printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
		return;
	}
	*beep = Mix_LoadWAV(audio_file);
	if (!beep) {
		printf("Failed to load beep.wav: %s\n", Mix_GetError());
		return;
	}
}
