#include <stdio.h>
#include <string.h>

typedef struct CHIP_8 {
	unsigned char MEMORY[4096]; 	// MEMORY
	unsigned char GPR[16];		// GENERAL PURPOSE REGISTERS 
	unsigned short INST_REG;	// INSTRUCTION REGISTER
	unsigned char DELAY_TIMER;	// DELAY TIMER
	unsigned char SOUND_TIMER;	// SOUND TIMER
	unsigned short STACK[16];	// STACK
	unsigned char SP; 		// STACK POINTER

	//NOTE: STILL WONDERING WHAT TO DO
	// unsigned char DISPLAY[64 * 32];
	// unsigned char KEY_PAD[16];

} CHIP_8;

// Function declarations
void init_GPR(unsigned char *GPR);
void init_MEMORY(unsigned char *MEMORY, FILE *FONT, FILE *ROM);
void init_INST_REG(unsigned short *INST_REG, unsigned char MEMORY_200, unsigned char MEMORY_201);
void init_DELAY_TIMER(unsigned char *DELAY_TIMER);
void init_SOUND_TIMER(unsigned char *SOUND_TIMER);
void init_STACK(unsigned short *STACK);
void init_SP(unsigned char *SP);

// Function definitions

//FIXME: 
//[X] LOAD FONT DATA
//[X] LOAD ROM

void init_MEMORY(unsigned char *MEMORY, FILE *FONT, FILE *ROM) {
	// Clear all memory
	memset(MEMORY, 0, 4096);

	// Optionally, load font data into MEMORY[0x000-0x1FF]
	//TODO: [X] LOAD FONT at MEMORY[0x000-0x1FF]
	int font_read_result = fread(&MEMORY[0x000], sizeof(unsigned char), 0x200, FONT);
	if (font_read_result == 0) {
		fprintf(stderr, "Error: Failed to load FONT.\n");
		// You can exit or handle the error as needed
	}
	//TODO: [X] LOAD ROM at MEMORY: 0x200
	
	int rom_read_result = fread(&MEMORY[0x200], sizeof(unsigned char), 4096 - 0x200, ROM);
	if (rom_read_result == 0) {
		fprintf(stderr, "Error: Failed to load ROM.\n");
		// You can exit or handle the error as needed
	}
}

void init_GPR(unsigned char *GPR) {
	memset(GPR, 0, 16);
}

void init_STACK(unsigned short *STACK) {
	memset(STACK, 0, 16 * sizeof(unsigned short));
}

void init_INST_REG(unsigned short *INST_REG, unsigned char MEMORY_200, unsigned char MEMORY_201) {
	*INST_REG = (MEMORY_200 << 8) | MEMORY_201;
}

void init_DELAY_TIMER(unsigned char *DELAY_TIMER) {
	*DELAY_TIMER = 0;
}

void init_SOUND_TIMER(unsigned char *SOUND_TIMER) {
	*SOUND_TIMER = 0;
}

void init_SP(unsigned char *SP) {
	*SP = 0;
}

CHIP_8 init_EMU(FILE *FONT, FILE *ROM) {
	CHIP_8 EMULATOR;

	init_MEMORY(EMULATOR.MEMORY, FONT, ROM);
	init_GPR(EMULATOR.GPR);
	init_INST_REG(&EMULATOR.INST_REG, EMULATOR.MEMORY[0x200], EMULATOR.MEMORY[0x201]);
	init_DELAY_TIMER(&EMULATOR.DELAY_TIMER);
	init_SOUND_TIMER(&EMULATOR.SOUND_TIMER);
	init_STACK(EMULATOR.STACK);
	init_SP(&EMULATOR.SP);

	return EMULATOR;
}

