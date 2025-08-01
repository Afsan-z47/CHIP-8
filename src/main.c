#include <stdio.h>
#include "chip8.h"

void fetch();
void decode();
void execute();

void fetch(CHIP_8 *EMULATOR){
	EMULATOR->INST_REG = EMULATOR->MEMORY[EMULATOR->PC] << 8 | EMULATOR->MEMORY[EMULATOR->PC + 1];
	EMULATOR->PC += 2;
}

CHIP_8 chip;

void decode(CHIP_8 *EMULATOR){
	
}

int main(int argc, char **argv){
	// Set up render system and register input callbacks
	init_Graphics();
	init_Input();

	// Initialize the CHIP-8 system
	// Load necessary Information
	chip = init_EMU(FILE *FONT, FILE *ROM);

	// Emulate loop
	
	for(;;){
		// Emulate one cycle
		emulate_cycle(&chip);

		//If the draw flag is set, update the screen
		if(chip.drawflag)
			draw_Graphics();

		// Store key press state (Press and Release);
		set_Keys(&chip);
	

	}

	return 0;

}
