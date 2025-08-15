#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include "display.h"
#include "input.h"

CHIP_8 chip;

void print_key(CHIP_8 chip){
	printf("%d %d %d %d\n", chip.KEY_PAD[0], chip.KEY_PAD[1], chip.KEY_PAD[2], chip.KEY_PAD[3]);
	printf("%d %d %d %d\n", chip.KEY_PAD[4], chip.KEY_PAD[5], chip.KEY_PAD[6], chip.KEY_PAD[7]);
	printf("%d %d %d %d\n", chip.KEY_PAD[8], chip.KEY_PAD[9], chip.KEY_PAD[10], chip.KEY_PAD[11]);
	printf("%d %d %d %d\n", chip.KEY_PAD[12], chip.KEY_PAD[13], chip.KEY_PAD[14], chip.KEY_PAD[15]);
	printf("DELAY TIMER: %d\n", chip.DELAY_TIMER);
	printf("LATCH HALT: %d\n", LATCH_KEY);
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
		//		print_key(chip);
		emulateCycle(&chip);
		//If the draw flag is set, update the screen
		// Update timers
		unsigned int new_tick = SDL_GetTicks();
		//printf("TICK := %d        chip := %d\n", new_tick, chip.TICK);
		//printf("Diff := %d\n", new_tick - chip.TICK);
		if( (new_tick - chip.TICK) >= 1000/60){
		printf("TICK := %d        chip := %d\n", new_tick, chip.TICK);
			if (chip.DELAY_TIMER > 0)
				--chip.DELAY_TIMER;

			if (chip. SOUND_TIMER > 0) {
				if (chip.SOUND_TIMER == 1)
					printf("BEEP!\n");
				--chip.SOUND_TIMER;
			}
			
			//GET KEYBOARD INPUT
			int is_quit = key_input(EVENT);
			if(is_quit) {
				fclose(ROM);
				return 0;
			}

			//DRAW IN DISPLAY
			if(chip.DRAW_FLAG)
				draw_Graphics(&chip);

			chip.TICK = new_tick;
		}
		// Store key press state (Press and Release);
		//set_Keys(&chip);
		//FIXME: The 60 Hz thing needs to be fixed
		SDL_Delay(1);
	}

	//	return 0;

}
