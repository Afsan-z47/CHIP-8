#include "debugger.h"
#include <stdio.h>
#include <stdlib.h>

void initDebugger(CHIP8_Debugger *dbg, const char *fontPath, int fontSize) {
    dbg->numBreakpoints = 0;
    dbg->stepping = 0;
    
    if (TTF_Init() < 0) {
        fprintf(stderr, "SDL_ttf could not initialize: %s\n", TTF_GetError());
        exit(1);
    }

    dbg->font = TTF_OpenFont(fontPath, fontSize);
    if (!dbg->font) {
        fprintf(stderr, "Failed to load font: %s\n", TTF_GetError());
        exit(1);
    }
}

void addBreakpoint(CHIP8_Debugger *dbg, uint16_t addr) {
    if(dbg->numBreakpoints < MAX_BREAKPOINTS)
        dbg->breakpoints[dbg->numBreakpoints++] = addr;
}

int isBreakpoint(CHIP8_Debugger *dbg, uint16_t pc) {
    for(int i = 0; i < dbg->numBreakpoints; i++)
        if(dbg->breakpoints[i] == pc) return 1;
    return 0;
}

void drawDebuggerPanel(CHIP_8 *chip, CHIP8_Debugger *dbg, SDL_Renderer *renderer, int xOffset, int yOffset, int lineHeight) {
    char buffer[128];
    SDL_Color white = {255, 255, 255, 255};
    
    int y = yOffset;

    // Draw PC
    sprintf(buffer, "PC: 0x%03X OPC: 0x%04X", chip->PC, chip->OPCODE);
    SDL_Surface *surf = TTF_RenderText_Solid(dbg->font, buffer, white);
    SDL_Texture *tex = SDL_CreateTextureFromSurface(renderer, surf);
    SDL_Rect dst = {xOffset, y, surf->w, surf->h};
    SDL_RenderCopy(renderer, tex, NULL, &dst);
    SDL_FreeSurface(surf); SDL_DestroyTexture(tex);
    y += lineHeight;

    // Draw Index register
    sprintf(buffer, "I: 0x%03X", chip->Index_REG);
    surf = TTF_RenderText_Solid(dbg->font, buffer, white);
    tex = SDL_CreateTextureFromSurface(renderer, surf);
    dst = (SDL_Rect){xOffset, y, surf->w, surf->h};
    SDL_RenderCopy(renderer, tex, NULL, &dst);
    SDL_FreeSurface(surf); SDL_DestroyTexture(tex);
    y += lineHeight;

    // Draw GPRs V0-VF
    for(int i=0;i<16;i++){
        sprintf(buffer, "V%X: %02X", i, chip->GPR[i]);
        surf = TTF_RenderText_Solid(dbg->font, buffer, white);
        tex = SDL_CreateTextureFromSurface(renderer, surf);
        dst = (SDL_Rect){xOffset + (i%4)*60, y + (i/4)*lineHeight, surf->w, surf->h};
        SDL_RenderCopy(renderer, tex, NULL, &dst);
        SDL_FreeSurface(surf); SDL_DestroyTexture(tex);
    }
    y += 4*lineHeight;

    // Draw Stack
    sprintf(buffer, "SP: %d Stack:", chip->SP);
    surf = TTF_RenderText_Solid(dbg->font, buffer, white);
    tex = SDL_CreateTextureFromSurface(renderer, surf);
    dst = (SDL_Rect){xOffset, y, surf->w, surf->h};
    SDL_RenderCopy(renderer, tex, NULL, &dst);
    SDL_FreeSurface(surf); SDL_DestroyTexture(tex);
    y += lineHeight;

    for(int i=0;i<chip->SP;i++){
        sprintf(buffer, "%02X ", chip->STACK[i]);
        surf = TTF_RenderText_Solid(dbg->font, buffer, white);
        tex = SDL_CreateTextureFromSurface(renderer, surf);
        dst = (SDL_Rect){xOffset + i*30, y, surf->w, surf->h};
        SDL_RenderCopy(renderer, tex, NULL, &dst);
        SDL_FreeSurface(surf); SDL_DestroyTexture(tex);
    }
    y += lineHeight;

    // Timers
    sprintf(buffer, "Delay: %d  Sound: %d", chip->DELAY_TIMER, chip->SOUND_TIMER);
    surf = TTF_RenderText_Solid(dbg->font, buffer, white);
    tex = SDL_CreateTextureFromSurface(renderer, surf);
    dst = (SDL_Rect){xOffset, y, surf->w, surf->h};
    SDL_RenderCopy(renderer, tex, NULL, &dst);
    SDL_FreeSurface(surf); SDL_DestroyTexture(tex);
}

void handleDebuggerEvents(CHIP8_Debugger *dbg) {
    SDL_Event e;
    while(SDL_PollEvent(&e)) {
        if(e.type == SDL_KEYDOWN) {
            if(e.key.keysym.sym == SDLK_s) dbg->stepping = 1; // Step
            else if(e.key.keysym.sym == SDLK_c) dbg->stepping = 0; // Continue
            else if(e.key.keysym.sym == SDLK_q) exit(0); // Quit
        }
    }
}
