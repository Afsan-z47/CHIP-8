#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "chip8.h"

// Function definitions

//FIXME: 
//[X] LOAD FONT DATA
//[X] LOAD ROM

void init_MEMORY(unsigned char *MEMORY, FILE *ROM) {
	// Clear all memory
	memset(MEMORY, 0, 4096);

	//TODO: [X] LOAD ROM at MEMORY: 0x200

	int rom_read_result = fread(&MEMORY[0x200], sizeof(unsigned char), 4096 - 0x200, ROM);
	if (rom_read_result == 0) {
		fprintf(stderr, "Error: Failed to load ROM.\n");
		// You can exit or handle the error as needed
	}


	// Optionally, load font data into MEMORY[0x000-0x1FF]
	//TODO: [X] LOAD FONT at MEMORY[0x050-0x080]
	unsigned char chip8_fontset[80] =
		{ 
			0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
			0x20, 0x60, 0x20, 0x20, 0x70, // 1
			0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
			0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
			0x90, 0x90, 0xF0, 0x10, 0x10, // 4
			0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
			0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
			0xF0, 0x10, 0x20, 0x40, 0x40, // 7
			0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
			0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
			0xF0, 0x90, 0xF0, 0x90, 0x90, // A
			0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
			0xF0, 0x80, 0x80, 0x80, 0xF0, // C
			0xE0, 0x90, 0x90, 0x90, 0xE0, // D
			0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
			0xF0, 0x80, 0xF0, 0x80, 0x80  // F
		};

	memcpy(&MEMORY[0x050], chip8_fontset, 80);


}

void init_GPR(unsigned char *GPR) {
	memset(GPR, 0, 16);
}

void init_STACK(unsigned short *STACK) {
	memset(STACK, 0, 16 * sizeof(unsigned short));
}

CHIP_8 init_EMU(FILE *ROM) {
	CHIP_8 EMULATOR;

	init_MEMORY(EMULATOR.MEMORY, ROM);
	init_GPR(EMULATOR.GPR);
	init_STACK(EMULATOR.STACK);

	EMULATOR.OPCODE = 0;
	EMULATOR.SP  = 0;
	EMULATOR.PC = 0x200;

	// Reset TImers
	EMULATOR.DELAY_TIMER = 0;
	EMULATOR.SOUND_TIMER = 0;

	return EMULATOR;
}


// NOTE: LIST OF OPCODES AND THEIR PROCESSESS
// [O] 00E0     Clear display 			
// [x] 00EE     Return from subroutine
// [O] 1NNN     Jump to NNN 
// [x] 2NNN     Call subroutine at NNN 
// [O] 3XKK     Skip next instruction if VX == KK 
// [O] 4XKK     Skip next instruction if VX <> KK  (Probably VX != KK)
// [O] 5XY0     Skip next instruction if VX == VY 
// [O] 6XKK     VX := KK 
// [O] 7XKK     VX := VX + KK 
// [x] 8XY0     VX := VY, VF may change 
// [x] 8XY1     VX := VX or VY, VF may change 
// [x] 8XY2     VX := VX and VY, VF may change 
// [x] 8XY3     VX := VX xor VY, VF may change
// [x] 8XY4     VX := VX + VY, VF := carry 
// [x] 8XY5     VX := VX - VY, VF := not borrow 
// [x] 8XY6     VX := VX shr 1, VF := carry 
// [x] 8XY7     VX := VY - VX, VF := not borrow
// [x] 8XYE     VX := VX shl 1, VF := carry 
// [O] 9XY0     Skip next instruction if VX <> VY 
// [O] ANNN     I := NNN 
// [x] BNNN     Jump to NNN+V0 
// [x] CXKK     VX := pseudorandom_number and KK 
//          collision. If N=0 and extended mode, show 16x16 sprite.
// [O] DXYN    Show N-byte sprite from M(I) at coords (VX,VY), VF :=
//          collision. If N=0 and extended mode, show 16x16 sprite.
// [x] EX9E     Skip next instruction if key VX pressed 
// [x] EXA1     Skip next instruction if key VX not pressed 
// [x] FX07     VX := delay_timer 
// [x] FX0A     wait for keypress, store hex value of key in VX 
// [x] FX15     delay_timer := VX 
// [x] FX18     sound_timer := VX 
// [x] FX1E     I := I + VX 
// [ ] FX29     Point I to 5-byte font sprite for hex character VX 
// [x] FX33     Store BCD representation of VX in M(I)..M(I+2) 
// [x] FX55     Store V0..VX in memory starting at M(I) 
// [x] FX65     Read V0..VX from memory starting at M(I)




void emulateCycle(CHIP_8 *chip) {
	// Fetch OPCODE
	chip->OPCODE = chip->MEMORY[chip->PC] << 8 | chip->MEMORY[chip->PC + 1];
	chip->PC += 2;

	// Decode OPCODE

	// Added as much I could find in my readings

	switch (chip->OPCODE & 0xF000)  //FIXME:   [1000 1111 1010 0101] & [1111 0000 0000 0000] == [1000 0000 0000 0000]
	{
		case 0xA000: // ANNN: Sets I to the address NNN
			chip->Index_REG = chip->OPCODE & 0x0FFF;
			break;

		//NOTE: A type that needs a more regorous opcode detection
		case 0x0000:
			switch(chip->OPCODE & 0x000F)
			{
				case 0x0000: // 0x00E0: Clears the screen        
					memset(chip->DISPLAY, 0 , 64*32);
					break;

				case 0x000E: // 0x00EE: Returns from subroutine          
					// Execute opcode
					chip->PC = chip->STACK[chip->SP - 1];
					chip->SP --;

					break;

				default:
					printf ("Unknown opcode [0x0000]: 0x%X\n", chip->OPCODE);          
			}
			break;

		case 0x1000: // 1NNN: Jump to NNN
			// FIXME: LOOK for some increment problem here
			// I did not send back pc by 2
			// After testing this part will be decided
			chip->PC = chip->OPCODE & 0x0FFF;
			break;


		//FIXME: THESE EXAMPLES MAY NOT WORK. JUST ADDING THEM FOR NOW.

		case 0x2000: // 2NNN: Call subroutine
			chip->STACK[chip->SP] = chip->PC; //FIXME: PC was incremented before this. The code may be wrong.
			chip->SP ++;
			chip->PC = chip->OPCODE & 0x0FFF;
			break;

		//NOTE: 4 Branch Instructions
		// [x] 3XNN
		// [x] 4XNN
		// [x] 5XY0
		// [x] 9XY0
		case 0x3000:
			if((chip->GPR[(chip->OPCODE & 0x0F00) >> 8]) == (chip->OPCODE & 0x00FF)) 
				chip->PC += 2;
			break;
		case 0x4000:
			if((chip->GPR[(chip->OPCODE & 0x0F00) >> 8]) != (chip->OPCODE & 0x00FF)) 
				chip->PC += 2;
			break;
		case 0x5000:
			if((chip->GPR[(chip->OPCODE & 0x0F00) >> 8 ]) == (chip->GPR[(chip->OPCODE & 0x00F0) >> 4]))
				chip->PC += 2;
			break;
		case 0x9000:
			if((chip->GPR[(chip->OPCODE & 0x0F00) >> 8 ]) != (chip->GPR[(chip->OPCODE & 0x00F0) >> 4]))
				chip->PC += 2;
			break;

		//NOTE: 10 Arithmetic Instructions
		// [x] 6XKK     VX := KK 
		// [x] 7XKK     VX := VX + KK 
		// [x] 8XY0     VX := VY, VF may change 
		// [x] 8XY1     VX := VX or VY, VF may change 
		// [x] 8XY2     VX := VX and VY, VF may change 
		// [x] 8XY3     VX := VX xor VY, VF may change
		// [x] 8XY4     VX := VX + VY, VF := carry 
		// [x] 8XY5     VX := VX - VY, VF := not borrow 
		// [x] 8XY6     VX := VX shr 1, VF := carry 
		// [x] 8XY7     VX := VY - VX, VF := not borrow
		// [x] 8XYE     VX := VX shl 1, VF := carry 


		case 0x6000: // 6XKK: VX := KK
			chip->GPR[(chip->OPCODE & 0x0F00) >> 8] = chip->OPCODE & 0x00FF;
			break;

		case 0x7000: // 7XKK: VX := VX + KK
			chip->GPR[(chip->OPCODE & 0x0F00) >> 8] += chip->OPCODE & 0x00FF;
			break;

		case 0x8000:
			switch (chip->OPCODE & 0x000F) {
				case 0x0000:
					chip->GPR[(chip->OPCODE & 0x0F00) >> 8] = chip->GPR[(chip->OPCODE & 0x00F0) >> 4];
					break;
				case 0x0001:
					chip->GPR[(chip->OPCODE & 0x0F00) >> 8] = chip->GPR[(chip->OPCODE & 0x0F00) >>8] | chip->GPR[(chip->OPCODE & 0x00F0) >> 4];
					break;

				case 0x0002:
					chip->GPR[(chip->OPCODE & 0x0F00) >> 8] = chip->GPR[(chip->OPCODE & 0x0F00) >> 8] & chip->GPR[(chip->OPCODE & 0x00F0) >> 4];
					break;

				case 0x0003:
					chip->GPR[(chip->OPCODE & 0x0F00) >> 8] = chip->GPR[(chip->OPCODE & 0x0F00) >> 8] ^ chip->GPR[(chip->OPCODE & 0x00F0) >> 4];
					break;

				case 0x0004:
					unsigned short temp_0 = (unsigned short)chip->GPR[(chip->OPCODE & 0x0F00) >> 8] + (unsigned short)chip->GPR[(chip->OPCODE & 0x00F0) >> 4];
					chip->GPR[(chip->OPCODE & 0x0F00) >> 8] = chip->GPR[(chip->OPCODE & 0x0F00) >> 8] + chip->GPR[(chip->OPCODE & 0x00F0) >> 4];

					if( temp_0 > 255)
						chip->GPR[15] = 1;
					else chip->GPR[15] = 0;
					break;


				case 0x0005:

					unsigned char temp_1 = chip->GPR[(chip->OPCODE & 0x0F00) >> 8];
					chip->GPR[(chip->OPCODE & 0x0F00) >> 8] = chip->GPR[(chip->OPCODE & 0x0F00) >> 8] - chip->GPR[(chip->OPCODE & 0x00F0) >> 4];

					if( (chip->GPR[(chip->OPCODE & 0x0F00) >> 8]) > temp_1 ) 
						chip->GPR[15] = 0;
					else chip->GPR[15] = 1;



					break;


				case 0x0007:

					chip->GPR[(chip->OPCODE & 0x0F00) >> 8] = chip->GPR[(chip->OPCODE & 0x00F0) >> 4] - chip->GPR[(chip->OPCODE & 0x0F00) >> 8];
					if( chip->GPR[(chip->OPCODE & 0x00F0) >> 4] > chip->GPR[(chip->OPCODE & 0x0F00) >> 8]) 
						chip->GPR[15] = 1;
					else chip->GPR[15] = 0;


					break;
				case 0x0006: // SHR VX
					{
						unsigned char x = (chip->OPCODE & 0x0F00) >> 8;
						unsigned char y = (chip->OPCODE & 0x00F0) >> 4;
						unsigned char lsb = chip->GPR[x] & 0x01; 
						chip->GPR[x] >>= 1;
						chip->GPR[15] = lsb ; // LSB before shift
					}
					break;

				case 0x000E: // SHL VX
					{
						unsigned char x = (chip->OPCODE & 0x0F00) >> 8;
						unsigned char y = (chip->OPCODE & 0x00F0) >> 4;
						unsigned char msb = (chip->GPR[x] & 0x80) >> 7;
						chip->GPR[x] <<= 1;
						chip->GPR[15] = msb; // MSB before shift
					}
					break;
			}
			break;

		//FIXME: Some of these implementations belong to a greater set
		// Like this one. It belongs to the class of 8. But only 8XY4 is implemented
		// Besure to complete these.
		/*
			case 0x0004: // 8XY4: VX := VX + VY, VF := carry
			if(chip->GPR[(chip->OPCODE & 0x00F0) >> 4] > (0xFF - chip->GPR[(chip->OPCODE & 0x0F00) >> 8]))
				chip->GPR[0xF] = 1; // carry
			else
				chip->GPR[0xF] = 0;
			chip->GPR[(chip->OPCODE & 0x0F00) >> 8] += chip->GPR[(chip->OPCODE & 0x00F0) >> 4];
			//	chip->PC += 2; //NOTE: Already added this at the start
			break;
		*/
		//FIXME: Error in specification
		// In the original COSMAC VIP interpreter, this instruction jumped to the address NNN plus the value in the register V0. This was mainly used for “jump tables”, to quickly be able to jump to different subroutines based on some input.
		//Starting with CHIP-48 and SUPER-CHIP, it was (probably unintentionally) changed to work as BXNN: It will jump to the address XNN, plus the value in the register VX. So the instruction B220 will jump to address 220 plus the value in the register V2.
		//The BNNN instruction was not widely used, so you might be able to just implement the first behavior (if you pick one, that’s definitely the one to go with). If you want to support a wide range of CHIP-8 programs, make this “quirk” configurable.

		case 0xB000:
			chip->PC = (chip->OPCODE & 0x0FFF) + chip->GPR[0];
			break;

		case 0xC000:
			chip->GPR[(chip->OPCODE & 0x0F00) >> 8] = rand() & (chip->OPCODE & 0x00FF);
			break;

		//FIXME: Another one that belongs to the class of F


		//NOTE: This one handles input
		//NOTE: Look how this one is handling the E class
		case 0xE000:
			switch(chip->OPCODE & 0x00FF)
			{
				// EX9E: Skips the next instruction 
				// if the key stored in VX is pressed
				case 0x009E:
					//	if(chip.KEY[chip->GPR[(chip->OPCODE & 0x0F00) >> 8]] != 0)
					//		chip->PC += 4;
					//	else
					//		chip->PC += 2;
					//NOTE: Commmented the code for adjustment of PC increment at the start
					if(chip->KEY_PAD[chip->GPR[(chip->OPCODE & 0x0F00) >> 8]] != 0)
						chip->PC += 2;
					break;

				case 0x00A1:
					if(chip->KEY_PAD[chip->GPR[(chip->OPCODE & 0x0F00) >> 8]] == 0)
						chip->PC += 2;
					break;


				default:
					printf("Unknown OPCODE: 0x%X\n", chip->OPCODE);
			}
			break;

		//TODO:
		// [x] FX07     VX := delay_timer 
		// [x] FX0A     wait for keypress, store hex value of key in VX 
		// [x] FX15     delay_timer := VX 
		// [x] FX18     sound_timer := VX 
		// [x] FX1E     I := I + VX 
		// [ ] FX29     Point I to 5-byte font sprite for hex character VX 
		// [x] FX33     Store BCD representation of VX in M(I)..M(I+2) 
		// [x] FX55     Store V0..VX in memory starting at M(I) 
		// [x] FX65     Read V0..VX from memory starting at M(I)



		case 0xF000:
			switch(chip->OPCODE & 0x00FF)
			{
				case 0x0007:
					chip->GPR[(chip->OPCODE & 0x0F00) >> 8] = chip->DELAY_TIMER;
					break;
				case 0x000A:
					if( (   chip->KEY_PAD[0] ||
						chip->KEY_PAD[1] ||
						chip->KEY_PAD[2] ||
						chip->KEY_PAD[3] ||
						chip->KEY_PAD[4] ||
						chip->KEY_PAD[5] ||
						chip->KEY_PAD[6] ||
						chip->KEY_PAD[7] ||
						chip->KEY_PAD[8] ||
						chip->KEY_PAD[9] ||
						chip->KEY_PAD[10] ||
						chip->KEY_PAD[11] ||
						chip->KEY_PAD[12] ||
						chip->KEY_PAD[13] ||
						chip->KEY_PAD[14] ||
						chip->KEY_PAD[15]) == 0 
					) chip->PC -= 2;

					break;
				case 0x0015:
					chip->DELAY_TIMER = chip->GPR[(chip->OPCODE & 0x0F00) >> 8];

					break;
				case 0x0018:
					chip->SOUND_TIMER = chip->GPR[(chip->OPCODE & 0x0F00) >> 8];

					break;
				case 0x001E:
					chip->Index_REG += chip->GPR[(chip->OPCODE & 0x0F00) >> 8];
					break;
				case 0x0029:

					break;
				case 0x0033: // FX33: Store BCD representation of VX in M(I)..M(I+2)
					chip->MEMORY[chip->Index_REG]     = chip->GPR[(chip->OPCODE & 0x0F00) >> 8] / 100;
					chip->MEMORY[chip->Index_REG + 1] = (chip->GPR[(chip->OPCODE & 0x0F00) >> 8] / 10) % 10;
					chip->MEMORY[chip->Index_REG + 2] = (chip->GPR[(chip->OPCODE & 0x0F00) >> 8] % 100) % 10;
					//	chip->PC += 2; //NOTE: Already incremented PC at the start
					break;				
				case 0x0055:
					for(int i=0; i <= (chip->OPCODE & 0x0F00) >> 8; i++){
						chip->MEMORY[chip->Index_REG + i] = chip->GPR[i];
					}
					break;
				case 0x0065:
					for(int i=0; i <= (chip->OPCODE & 0x0F00) >> 8; i++){
						chip->GPR[i] = chip->MEMORY[chip->Index_REG + i];
					}
					break;

				default:
					printf("Unknown OPCODE: 0x%X\n", chip->OPCODE);
			}
			break;



		//NOTE: This part Handles GRAPHICS

		//TODO: 
		// [x] 00E0     Clear display 
		// [x] 1NNN     Jump to NNN 
		// [x] 6XKK     VX := KK 
		// [x] 7XKK     VX := VX + KK 
		// [x] ANNN     I := NNN 
		// [x] DXYN     Show N-byte sprite from M(I) at coords (VX,VY), VF :=
		//              collision. If N=0 and extended mode, show 16x16 sprite.
		case 0xD000:		   
			{
				unsigned short x = chip->GPR[(chip->OPCODE & 0x0F00) >> 8];
				unsigned short y = chip->GPR[(chip->OPCODE & 0x00F0) >> 4];
				unsigned short height = chip->OPCODE & 0x000F;
				unsigned short pixel;

				chip->GPR[0xF] = 0;
				for (int yline = 0; yline < height; yline++)
				{
					pixel = chip->MEMORY[chip->Index_REG + yline];
					for(int xline = 0; xline < 8; xline++)
					{
						if((pixel & (0x80 >> xline)) != 0)
						{
							if(chip->DISPLAY[(x + xline + ((y + yline) * 64))] == 1)
								chip->GPR[0xF] = 1;
							chip->DISPLAY[x + xline + ((y + yline) * 64)] ^= 1;
						}
					}
				}

				chip->DRAW_FLAG = 1; // 1 == TRUE
				//chip->PC += 2; //NOTE: PC already Incremented at start
			}
			break;


	}

	// Update timers
	if (chip->DELAY_TIMER > 0)
		--chip->DELAY_TIMER;

	if (chip-> SOUND_TIMER > 0) {
		if (chip->SOUND_TIMER == 1)
			printf("BEEP!\n");
		--chip->SOUND_TIMER;
	}

	if ((chip->OPCODE & 0xF0FF) == 0xF029) printf("THE FONT CODE\n");
	printf("PC: %04X OPCODE: %04X\n", chip->PC, chip->OPCODE);

}
