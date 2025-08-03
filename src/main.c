#include <SDL2/SDL_events.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include "chip8.h"
#include "display.h"

CHIP_8 chip;

void decode(CHIP_8 *EMULATOR){

}

int main(int argc, char **argv){

	if(argc < 2) {
		fprintf(stderr, "Usage: %s <ROM file>\n", argv[0]);
	}

	// Open ROM file
	FILE *ROM = fopen( argv[1], "rb");
	if (!ROM) {
		perror("Failed to open ROM file");
		return 1;
	}
	//FIXME: Event Handler
	SDL_Event EVENT;


	// Set up render system and register input callbacks
	//NOTE: Getting the window ID for Keyboard Initiailization
	init_Graphics(); 
	//init_keyboard(window);

	// Initialize the CHIP-8 system
	// Load necessary Information
	chip = init_EMU(ROM);

	// Emulate loop
	while(1) {
		// Emulate one cycle
		while(SDL_PollEvent( &EVENT)){
			if( EVENT.type == SDL_QUIT){
				//Destroy Stuff made stuff xD
				SDL_DestroyWindow(window);
				SDL_DestroyRenderer(renderer);
				//Quit SDL subsystem
				SDL_Quit();
				return 0;
			}
		}
		emulateCycle(&chip);

		//If the draw flag is set, update the screen
		if(chip.DRAW_FLAG)
			draw_Graphics(&chip);

		// Store key press state (Press and Release);
		//set_Keys(&chip);

		SDL_Delay(10);

	}

	return 0;

}
