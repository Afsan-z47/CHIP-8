#include <SDL2/SDL_events.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <string.h>
#include "chip8.h"
#include "display.h"

CHIP_8 chip;

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
			//User presses a key
			else if( EVENT.type == SDL_KEYDOWN){
				//Update key in chip8
				switch (EVENT.key.keysym.sym) 
				{
					case SDLK_1:
						chip.KEY_PAD[1] = 1;
						break;
					case SDLK_2:
						chip.KEY_PAD[2] = 1;
						break;
					case SDLK_3:
						chip.KEY_PAD[3] = 1;
						break;
					case SDLK_4:
						chip.KEY_PAD[12] = 1;
						break;
					case SDLK_q:
						chip.KEY_PAD[4] = 1;
						break;
					case SDLK_w:
						chip.KEY_PAD[5] = 1;
						break;
					case SDLK_e:
						chip.KEY_PAD[6] = 1;
						break;
					case SDLK_r:
						chip.KEY_PAD[13] = 1;
						break;
					case SDLK_a:
						chip.KEY_PAD[7] = 1;
						break;
					case SDLK_s:
						chip.KEY_PAD[8] = 1;
						break;
					case SDLK_d:
						chip.KEY_PAD[9] = 1;
						break;
					case SDLK_f:
						chip.KEY_PAD[14] = 1;
						break;
					case SDLK_z:
						chip.KEY_PAD[10] = 1;
						break;
					case SDLK_x:
						chip.KEY_PAD[0] = 1;
						break;
					case SDLK_c:
						chip.KEY_PAD[11] = 1;
						break;
					case SDLK_v:
						chip.KEY_PAD[15] = 1;
						break;
				}

			}
			else {

				memset(chip.KEY_PAD, 0, 16);
			}

		}
		emulateCycle(&chip);
		//If the draw flag is set, update the screen
		if(chip.DRAW_FLAG)
			draw_Graphics(&chip);

		// Store key press state (Press and Release);
		//set_Keys(&chip);
		//FIXME: The 60 Hz thing needs to be fixed
		SDL_Delay(10);

	}

	return 0;

}
