#include "input.h"

int key_input(SDL_Event EVENT){
	while(SDL_PollEvent( &EVENT)){
		if( EVENT.type == SDL_QUIT){
			//Destroy Stuff made stuff xD
			SDL_DestroyWindow(window);
			SDL_DestroyRenderer(renderer);
			//Quit SDL subsystem
			SDL_Quit();
			return 1;
		}
		//User presses a key
		else if( EVENT.type == SDL_KEYDOWN){
			//Update key in chip8
			switch (EVENT.key.keysym.sym) 
			{
				case SDLK_1: chip.KEY_PAD[1] = 1; break;
				case SDLK_2: chip.KEY_PAD[2] = 1; break;
				case SDLK_3: chip.KEY_PAD[3] = 1; break;
				case SDLK_4: chip.KEY_PAD[12] = 1; break;
				case SDLK_q: chip.KEY_PAD[4] = 1; break;
				case SDLK_w: chip.KEY_PAD[5] = 1; break;
				case SDLK_e: chip.KEY_PAD[6] = 1; break;
				case SDLK_r: chip.KEY_PAD[13] = 1; break;
				case SDLK_a: chip.KEY_PAD[7] = 1; break;
				case SDLK_s: chip.KEY_PAD[8] = 1; break;
				case SDLK_d: chip.KEY_PAD[9] = 1; break;
				case SDLK_f: chip.KEY_PAD[14] = 1; break;
				case SDLK_z: chip.KEY_PAD[10] = 1; break;
				case SDLK_x: chip.KEY_PAD[0] = 1; break;
				case SDLK_c: chip.KEY_PAD[11] = 1; break;
				case SDLK_v: chip.KEY_PAD[15] = 1; break;
				case SDLK_ESCAPE: 
					//Destroy Stuff made stuff xD
					SDL_DestroyWindow(window);
					SDL_DestroyRenderer(renderer);
					//Quit SDL subsystem
					SDL_Quit();
					return 1;
			}
		}
		else if( EVENT.type == SDL_KEYUP){
			//Update key in chip8
			switch (EVENT.key.keysym.sym) 
			{
				case SDLK_1: chip.KEY_PAD[1] = 0; break;
				case SDLK_2: chip.KEY_PAD[2] = 0; break;
				case SDLK_3: chip.KEY_PAD[3] = 0; break;
				case SDLK_4: chip.KEY_PAD[12] = 0; break;
				case SDLK_q: chip.KEY_PAD[4] = 0; break;
				case SDLK_w: chip.KEY_PAD[5] = 0; break;
				case SDLK_e: chip.KEY_PAD[6] = 0; break;
				case SDLK_r: chip.KEY_PAD[13] = 0; break;
				case SDLK_a: chip.KEY_PAD[7] = 0; break;
				case SDLK_s: chip.KEY_PAD[8] = 0; break;
				case SDLK_d: chip.KEY_PAD[9] = 0; break;
				case SDLK_f: chip.KEY_PAD[14] = 0; break;
				case SDLK_z: chip.KEY_PAD[10] = 0; break;
				case SDLK_x: chip.KEY_PAD[0] = 0; break;
				case SDLK_c: chip.KEY_PAD[11] = 0; break;
				case SDLK_v: chip.KEY_PAD[15] = 0; break;
			}


		}

	}
	return 0;
}

