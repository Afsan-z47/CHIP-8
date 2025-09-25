#ifndef CHIP8_DEBUGGER_H
#define CHIP8_DEBUGGER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "chip8.h"

#define MAX_BREAKPOINTS 32

typedef struct {
    uint16_t breakpoints[MAX_BREAKPOINTS];
    int numBreakpoints;
    int stepping; // 0 = continue, 1 = step mode
    TTF_Font *font; // SDL_ttf font for debugger text
} CHIP8_Debugger;

// Breakpoint functions
void initDebugger(CHIP8_Debugger *dbg, const char *fontPath, int fontSize);
void addBreakpoint(CHIP8_Debugger *dbg, uint16_t addr);
int isBreakpoint(CHIP8_Debugger *dbg, uint16_t pc);

// Draw debugger panel beside Chip-8 screen
void drawDebuggerPanel(CHIP_8 *chip, CHIP8_Debugger *dbg, SDL_Renderer *renderer, int xOffset, int yOffset, int lineHeight);

// Handle step/breakpoint events
void handleDebuggerEvents(CHIP8_Debugger *dbg);

#endif
