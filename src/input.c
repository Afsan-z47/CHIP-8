#include "input.h"
#include "display.h"
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <stdio.h>

#define REQUIRED_TERMINAL_LINES 23

int KEY[16] = { 
	SDLK_1,
	SDLK_2,
	SDLK_3,
	SDLK_4,
	SDLK_q,
	SDLK_w,
	SDLK_e,
	SDLK_r,
	SDLK_a,
	SDLK_s,
	SDLK_d,
	SDLK_f,
	SDLK_z,
	SDLK_x,
	SDLK_c,
	SDLK_v
};

int key_input(SDL_Event EVENT, CHIP_8 *chip){
	while(SDL_PollEvent( &EVENT)){
		if( EVENT.type == SDL_QUIT){
			return 1;
		}
		//User presses a key
		else if( EVENT.type == SDL_KEYDOWN){
			//Update key in chip->
			if(EVENT.key.keysym.sym == KEY[0]) { chip->KEY_PAD[1] = 1;  return 0;} 
			if(EVENT.key.keysym.sym == KEY[1]) { chip->KEY_PAD[2] = 1;  return 0;}
			if(EVENT.key.keysym.sym == KEY[2]) { chip->KEY_PAD[3] = 1;  return 0;}
			if(EVENT.key.keysym.sym == KEY[3]) { chip->KEY_PAD[12] = 1; return 0;}
			if(EVENT.key.keysym.sym == KEY[4]) { chip->KEY_PAD[4] = 1;  return 0;}
			if(EVENT.key.keysym.sym == KEY[5]) { chip->KEY_PAD[5] = 1;  return 0;}
			if(EVENT.key.keysym.sym == KEY[6]) { chip->KEY_PAD[6] = 1;  return 0;}
			if(EVENT.key.keysym.sym == KEY[7]) { chip->KEY_PAD[13] = 1; return 0;}
			if(EVENT.key.keysym.sym == KEY[8]) { chip->KEY_PAD[7] = 1;  return 0;}
			if(EVENT.key.keysym.sym == KEY[9]) { chip->KEY_PAD[8] = 1;  return 0;}
			if(EVENT.key.keysym.sym == KEY[10]) { chip->KEY_PAD[9] = 1;  return 0;}
			if(EVENT.key.keysym.sym == KEY[11]) { chip->KEY_PAD[14] = 1; return 0;}
			if(EVENT.key.keysym.sym == KEY[12]) { chip->KEY_PAD[10] = 1; return 0;}
			if(EVENT.key.keysym.sym == KEY[13]) { chip->KEY_PAD[0] = 1;  return 0;}
			if(EVENT.key.keysym.sym == KEY[14]) { chip->KEY_PAD[11] = 1; return 0;}
			if(EVENT.key.keysym.sym == KEY[15]) { chip->KEY_PAD[15] = 1; return 0;}
			if(EVENT.key.keysym.sym == SDLK_ESCAPE) return 1;

		}

		else if( EVENT.type == SDL_KEYUP){
			//Update key in chip
			if(EVENT.key.keysym.sym == KEY[0]) { chip->KEY_PAD[1] = 0;  return 0;} 
			if(EVENT.key.keysym.sym == KEY[1]) { chip->KEY_PAD[2] = 0;  return 0;}
			if(EVENT.key.keysym.sym == KEY[2]) { chip->KEY_PAD[3] = 0;  return 0;}
			if(EVENT.key.keysym.sym == KEY[3]) { chip->KEY_PAD[12] = 0; return 0;}
			if(EVENT.key.keysym.sym == KEY[4]) { chip->KEY_PAD[4] = 0;  return 0;}
			if(EVENT.key.keysym.sym == KEY[5]) { chip->KEY_PAD[5] = 0;  return 0;}
			if(EVENT.key.keysym.sym == KEY[6]) { chip->KEY_PAD[6] = 0;  return 0;}
			if(EVENT.key.keysym.sym == KEY[7]) { chip->KEY_PAD[13] = 0; return 0;}
			if(EVENT.key.keysym.sym == KEY[8]) { chip->KEY_PAD[7] = 0;  return 0;}
			if(EVENT.key.keysym.sym == KEY[9]) { chip->KEY_PAD[8] = 0;  return 0;}
			if(EVENT.key.keysym.sym == KEY[10]) { chip->KEY_PAD[9] = 0;  return 0;}
			if(EVENT.key.keysym.sym == KEY[11]) { chip->KEY_PAD[14] = 0; return 0;}
			if(EVENT.key.keysym.sym == KEY[12]) { chip->KEY_PAD[10] = 0; return 0;}
			if(EVENT.key.keysym.sym == KEY[13]) { chip->KEY_PAD[0] = 0;  return 0;}
			if(EVENT.key.keysym.sym == KEY[14]) { chip->KEY_PAD[11] = 0; return 0;}
			if(EVENT.key.keysym.sym == KEY[15]) { chip->KEY_PAD[15] = 0; return 0;}

		}
		else if ( EVENT.type == SDL_WINDOWEVENT){
			draw_Graphics(chip);
			//FIXME: The bug with memory leak can be observed if 
			//instead of using draw_Graphics using
			//SDL_RenderPresent(renderer);
		}

	}
	return 0;
}

void draw_layout() {

	//NOTE: Required line amount is being added
	for (int i = 0; i < REQUIRED_TERMINAL_LINES; i++) {
		printf("\n");
	}
	//NOTE: Going back to original position
	printf("\x1b[%dA", REQUIRED_TERMINAL_LINES);

	printf("\n- CHIP-8 Keypad -\n");
	printf(
		"┌───┬───┬───┬───┐\n"
		"│ 1 │ 2 │ 3 │ C │\n"
		"├───┼───┼───┼───┤\n"
		"│ 4 │ 5 │ 6 │ D │\n"
		"├───┼───┼───┼───┤\n"
		"│ 7 │ 8 │ 9 │ E │\n"
		"├───┼───┼───┼───┤\n"
		"│ A │ 0 │ B │ F │\n"
		"└───┴───┴───┴───┘\n"
	);
	printf(
		"┌───┬───┬───┬───┐\n"
		"│   │   │   │   │\n"
		"├───┼───┼───┼───┤\n"
		"│   │   │   │   │\n"
		"├───┼───┼───┼───┤\n"
		"│   │   │   │   │\n"
		"├───┼───┼───┼───┤\n"
		"│   │   │   │   │\n"
		"└───┴───┴───┴───┘\n"
	);

	printf("\x1b[9A");   // move up 9 lines (to the first "+---..."), then down 1 to first content row
	printf("\x1b[s");    // save this position as the "mapping origin"
	// Move back down to below the grid where we’ll show the prompt.
	printf("\x1b[9B");   // from origin row (content row 0), there are 9 lines to get below the last border
	fflush(stdout);
}

void move_to_prompt_line(){
	printf("\x1b[u"); // Load origin
	printf("\x1b[10B"); // 10 lines after origin.
}

void move_to_cell(unsigned char row, unsigned char column){
	// LOAD ORIGIN
	printf("\x1b[u");
	// MOVE DOWN
	printf("\x1b[%dB", 1 + row * 2); // 1 for initial extra space
	// MOVE RIGHT 
	printf("\x1b[%dC", 2 + column * 4); // 2 for initial extra spaces
}

void customize_keyboard(){

	unsigned char key_label[16] = {

		'1' , '2' , '3', 'C',
		'4' , '5' , '6', 'D',
		'7' , '8' , '9', 'E',
		'A' , '0' , 'B', 'F'

	};

	// Draw the necessary layout;
	draw_layout();

	unsigned char row;
	unsigned char column;

	//Here starts Mappings
	move_to_prompt_line();
	printf("Mapping . . . . . . . .\n");
	printf("Press a key for CHIP-8 0x%X (Key -> %c): ", 0, key_label[0]);


	for(int i=0; i<16; i++){
		row = (unsigned char)(i/4);
		column = (unsigned char)(i%4);


		//scan key
		scanf(" %c", (char *)&KEY[i]);

		// Input to Cell
		move_to_cell(row, column);
		printf("%c", KEY[i]);

		// Provide the next key instruction
		move_to_prompt_line();

		printf("Mapped 0x%X (%c) -> '%c'  [%d/16]\n", i, key_label[i], KEY[i], i + 1);
		if( i < 15 ) printf("Press a key for CHIP-8 0x%X (Key -> %c): ", i+1, key_label[i+1]);
		else {
			printf("\r\x1b[K\n"); // clear the status/prompt line
			printf("Customization Complete!\n");
			printf("=======================\n");
		};

		fflush(stdout);
	}
	printf("\n");
}


