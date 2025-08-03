#include <SDL2/SDL_events.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>
#include <SDL2/SDL.h>
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
			else if (EVENT.type == SDL_KEYDOWN || EVENT.type == SDL_KEYUP) {
				int is_pressed = (EVENT.type == SDL_KEYDOWN) ? 1 : 0;

				switch (EVENT.key.keysym.sym) {
					case SDLK_1: chip.KEY_PAD[1] = is_pressed; break;
					case SDLK_2: chip.KEY_PAD[2] = is_pressed; break;
					case SDLK_3: chip.KEY_PAD[3] = is_pressed; break;
					case SDLK_4: chip.KEY_PAD[12] = is_pressed; break;
					case SDLK_q: chip.KEY_PAD[4] = is_pressed; break;
					case SDLK_w: chip.KEY_PAD[5] = is_pressed; break;
					case SDLK_e: chip.KEY_PAD[6] = is_pressed; break;
					case SDLK_r: chip.KEY_PAD[13] = is_pressed; break;
					case SDLK_a: chip.KEY_PAD[7] = is_pressed; break;
					case SDLK_s: chip.KEY_PAD[8] = is_pressed; break;
					case SDLK_d: chip.KEY_PAD[9] = is_pressed; break;
					case SDLK_f: chip.KEY_PAD[14] = is_pressed; break;
					case SDLK_z: chip.KEY_PAD[10] = is_pressed; break;
					case SDLK_x: chip.KEY_PAD[0] = is_pressed; break;
					case SDLK_c: chip.KEY_PAD[11] = is_pressed; break;
					case SDLK_v: chip.KEY_PAD[15] = is_pressed; break;
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
	}
	return 0;
}

