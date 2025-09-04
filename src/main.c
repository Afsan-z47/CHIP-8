#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include <bits/getopt_core.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include "chip8.h"
#include "display.h"
#include "input.h"
#include "audio.h"
#include <unistd.h>


void print_key(CHIP_8 chip){
	printf("%d %d %d %d\n", chip.KEY_PAD[0], chip.KEY_PAD[1], chip.KEY_PAD[2], chip.KEY_PAD[3]);
	printf("%d %d %d %d\n", chip.KEY_PAD[4], chip.KEY_PAD[5], chip.KEY_PAD[6], chip.KEY_PAD[7]);
	printf("%d %d %d %d\n", chip.KEY_PAD[8], chip.KEY_PAD[9], chip.KEY_PAD[10], chip.KEY_PAD[11]);
	printf("%d %d %d %d\n", chip.KEY_PAD[12], chip.KEY_PAD[13], chip.KEY_PAD[14], chip.KEY_PAD[15]);
	printf("DELAY TIMER: %d\n", chip.DELAY_TIMER);
	printf("LATCH HALT: %d\n", LATCH_KEY);
}

int main(int argc, char **args){

	if (argc == 1) goto HELP;


	int option = 0;


	FILE* ROM = NULL;
	char* audio_file = "beep.wav";

	while ((option = getopt(argc, args, "a:r:hkc:SFJDVO")) != -1) {
		switch (option) {

			case 'h':
			HELP:
				printf("Usage: %s [options]\n", args[0]);
				printf("  -r <file>  -> rom <file>        ROM file to load\n");
				printf("  -d 	     -> debug             Enable debugger\n");
				printf("  -a <file>  -> audio <file.wav>  Audio file\n");
				printf("  -k 	     -> Customize Keyboard\n");
				printf("  -c <n>     -> color <value>     Set Pixel Color\n");
				printf("  Values for <n> is [RED] [BLUE] [GREEN] [YELLOW] [CYAN] [MAGENTA] [WHITE](default) \n");
				printf("  -h 	     -> help              Show this help\n");
				printf("  ==============================================\n");
				printf("  Ambiguous instruction flags\n");
				printf("  -S 	     -> Shift VY instead of Vx for [8XY6] and [8XYE]\n");
				printf("  -F 	     -> Change value of I for [FX55] and [FX56]\n");
				printf("  -J 	     -> Use VX instead of V0 for [BNNN]\n");
				printf("  -D 	     -> Stop CPU when rendering DISPLAY\n");
				printf("  -V 	     -> AND[8xy1], OR[8xy2], XOR[8xy3] resets VF to zero\n");
				printf("  -O 	     -> Original CHIP-8 behaviour\n");

				// Handle Quitting
				if (ROM) fclose(ROM);
				return 0;


			case 'a':
				audio_file = optarg;
				break;

			case 'r':
				// Open ROM file
				ROM = fopen( optarg, "rb");
				if (!ROM) {
					perror("Failed to open ROM file");
					return 1;
				}
				break;
			case 'c': 

				//TODO:
				//[ ] : Add more colors

				if (strncmp(optarg, "RED", 3) == 0) 	{ PIXEL_COLOR = RED;} 
				else if (strncmp(optarg, "GREEN", 5) == 0) 	{ PIXEL_COLOR = GREEN; } 
				else if (strncmp(optarg, "BLUE", 4) == 0) 	{ PIXEL_COLOR = BLUE; } 
				else if (strncmp(optarg, "WHITE", 5) == 0) 	{ PIXEL_COLOR = WHITE; } 
				else if (strncmp(optarg, "YELLOW", 6) == 0) 	{ PIXEL_COLOR = YELLOW; } 
				else if (strncmp(optarg, "CYAN", 4) == 0) 	{ PIXEL_COLOR = CYAN; } 
				else if (strncmp(optarg, "MAGENTA", 5) == 0) 	{ PIXEL_COLOR = MAGENTA; } 
				else 
				PIXEL_COLOR = (unsigned int) strtol(optarg, NULL, 0);

				break;
			case 'S':
				// 8xy[6E]: Put VY into VX before shift
				SHIFT_VY = !SHIFT_VY;
				break;
			case 'J':
				//Bnnn: Use VX instead of V0
				JUMP = !JUMP;
				break;
			case 'F':
				// FX[56]5: Change value of I
				FX_INCR_I = !FX_INCR_I;
				break;
			case 'D':
				// Stop CPU when rendering DISPLAY
				DISP_WAIT = !DISP_WAIT;
				break;

			//NOTE: The AND, OR and XOR opcodes (8xy1, 8xy2 and 8xy3) reset the flags register to zero.
			case 'V':

				VF_RESET = 1;
				break;
			case 'O':
				//Sets to the original CHIP-8 behaviour
				SHIFT_VY = 1;
				FX_INCR_I = 1;
				JUMP = 0;
				DISP_WAIT = 1;
				VF_RESET = 1;
				break;
			case 'k':
				customize_keyboard();
				break;
			case '?':
			default:
				fprintf(stderr, "Usage: %s [-d] [-r romfile] [-S scale] [-s soundfile.wav]\n", args[0]);
				return 1;
		}
	}




	//FIXME: Event Handler: Testing union initalizer
	SDL_Event EVENT = {} ; //NOTE: In C23 or C++, assigning {} to a union guarantees the clearing of a whole union including padding bits (except for static storage duration initialization)


	// Set up render system and register input callbacks
	//NOTE: Getting the window ID for Keyboard Initiailization
	SDL_Init(SDL_INIT_VIDEO);
	init_Graphics(); 

	//NOTE: For short sounds Mix_Chunk is used
	SDL_Init(SDL_INIT_AUDIO);
	Mix_Chunk *beep = NULL;
	init_audio(&beep, audio_file);
	//init_keyboard(window);

	// Initialize the CHIP-8 system
	// Load necessary Information
	CHIP_8 chip = init_EMU(ROM);

	// Emulate loop
	while(1) {
		// Emulate one cycle
		//print_key(chip);
		if(!(chip.DRAW_FLAG && DISP_WAIT))
		emulateCycle(&chip);
		//If the draw flag is set, update the screen
		// Update timers
		unsigned int new_tick = SDL_GetTicks();

		if( (new_tick - chip.TICK) >= 1000/60){
			//printf("TICK := %d        chip := %d\n", new_tick, chip.TICK);
			if (chip.DELAY_TIMER > 0)
				--chip.DELAY_TIMER;

			if (chip. SOUND_TIMER > 0) {
				if (chip.SOUND_TIMER == 1)
					//NOTE: MIX_PlayChannel(Target_Channel, Mix_Chunk, Repeatation);
					// Target_Channel = -1 for any channel
					Mix_PlayChannel(-1, beep, 0); // Play once
				--chip.SOUND_TIMER;
			}

			//GET KEYBOARD INPUT
			int is_quit = key_input(EVENT, &chip);

			//Ending program
			if(is_quit) break;
			
			//DRAW IN DISPLAY
			if(chip.DRAW_FLAG)
				draw_Graphics(&chip);

			//NOTE: Update Tick for next check
			chip.TICK = new_tick;
		}
		// Store key press state (Press and Release);
		//set_Keys(&chip);
		//FIXME: The 60 Hz thing needs to be fixed
		SDL_Delay(1);
	}
	
	//Ending program
	fclose(ROM);

	//Close audio
	Mix_FreeChunk(beep);
	Mix_CloseAudio();
	Mix_Quit();

	//Destroy Stuff xD
	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	//texture = NULL;
	//renderer = NULL;
	//window = NULL;
	
	//Quit SDL subsystem
	SDL_Quit();

	return 0;
}
