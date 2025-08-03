#include <stdio.h>

typedef struct CHIP_8 {
	unsigned char MEMORY[4096]; 	// MEMORY
	unsigned char GPR[16];		// GENERAL PURPOSE REGISTERS 
	unsigned short Index_REG;	// Index REGISTER
	unsigned short STACK[16];	// STACK
	unsigned char SP; 		// STACK POINTER
	unsigned short PC; 		// PROGRAM POINTER
	
	unsigned short OPCODE;		// OPCODE

	unsigned char DELAY_TIMER;	// DELAY TIMER
	unsigned char SOUND_TIMER;	// SOUND TIMER
	
	unsigned char DRAW_FLAG;	// DRAW FLAG

	unsigned char DISPLAY[64 * 32];
	unsigned char KEY_PAD[16];

} CHIP_8;

// Function declarations
void init_GPR(unsigned char *GPR);
void init_MEMORY(unsigned char *MEMORY,FILE *ROM);
void init_INST_REG(unsigned short *Index_REG, unsigned char MEMORY_200, unsigned char MEMORY_201);
void init_STACK(unsigned short *STACK);
CHIP_8 init_EMU(FILE *ROM);
void emulateCycle(CHIP_8 *chip);
