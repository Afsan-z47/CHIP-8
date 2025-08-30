#ifndef __CHIP8__
#define __CHIP8__

#include <stdio.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define WHITE 0xFFFFFFFF
#define BLACK 0x00000000
#define RED 0xFF0000FF


//#define BLACK   0x000000FF  // R=0   G=0   B=0   A=255
#define RED     0xFF0000FF  // R=255 G=0   B=0   A=255
#define GREEN   0x00FF00FF  // R=0   G=255 B=0   A=255
#define BLUE    0x0000FFFF  // R=0   G=0   B=255 A=255
#define YELLOW  0xFFFF00FF  // R=255 G=255 B=0   A=255
#define CYAN    0x00FFFFFF  // R=0   G=255 B=255 A=255
#define MAGENTA 0xFF00FFFF  // R=255 G=0   B=255 A=255


extern unsigned int PIXEL_COLOR;
extern unsigned int BACKGROUND_COLOR;
//#define PIXEL_COLOR (RED ^ BACKGROUND_COLOR)



extern unsigned char LATCH_KEY;
extern unsigned char SHIFT_VY;
extern unsigned char FX_INCR_I;
extern unsigned char JUMP;
extern unsigned char DISP_WAIT;
extern unsigned char VF_RESET;

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

	unsigned int DISPLAY[64 * 32];
	unsigned char KEY_PAD[16];
	unsigned int TICK;

} CHIP_8;

//extern CHIP_8 chip;

// Function declarations
void init_GPR(unsigned char *GPR);
void init_MEMORY(unsigned char *MEMORY,FILE *ROM);
void init_INST_REG(unsigned short *Index_REG, unsigned char MEMORY_200, unsigned char MEMORY_201);
void init_STACK(unsigned short *STACK);
CHIP_8 init_EMU(FILE *ROM);
void emulateCycle(CHIP_8 *chip);

#endif
