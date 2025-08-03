# Chip-8 Emulator with Debugger (C)

A Chip-8 emulator written in C with built-in debugger support.

## Features

- ✅ Full Chip-8 instruction set
- 🔍 Debugger: step, breakpoints, inspect memory/registers
- 📺 SDL2 display backend
- ⌨️ Keyboard input
- 🧪 Load ROMs for testing
## Compile
```bash
gcc main.c display.c chip8.c -o chip8 -lSDL2
```
## Build & Run

```bash
make
./build/chip8_debugger roms/your_rom.ch8

