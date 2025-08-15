#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>

void init_audio(Mix_Chunk **beep, char* audio_file){
	//NOTE:: Setting up the Device audio driver
	//To initialize SDL_mixer call Mix_OpenAudio. 
	//The first argument sets the sound frequency, and 44100 is a standard frequency that works on most systems. 
	//The second argument determines the sample format. Using the default MIX_DEFAULT_FORMAT. 
	//The third argument is the number of hardware channels. Using 2 channels for stereo. 
	//The last argument is the sample size, which determines the size of the chunks which is used when playing sound. 2048 bytes (AKA 2 kilobyes) worked fine.
	if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
	{
		printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
		return;
	}
	
	//NOTE: For loading the .wav file to Mix_Chunk
	*beep = Mix_LoadWAV(audio_file);
	
	if (!beep) {
		printf("Failed to load beep.wav: %s\n", Mix_GetError());
		return;
	}
}
