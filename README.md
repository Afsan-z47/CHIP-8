# CHIP-8 Emulator (C)

A Chip-8 emulator written in C with built-in debugger support.

## Features

- Full Chip-8 instruction set
- Debugger: step, breakpoints, inspect memory/registers
- SDL2 display backend
- Keyboard input
- Load ROMs for testing

## Compile

```sh
gcc main.c display.c chip8.c input.c -o chip8 -lSDL2
```

## Run

```sh
./chip8 roms/your_rom.ch8
```

## Test Status

Test ROMs from Timendus' [Chip-8 test suite](https://github.com/Timendus/chip8-test-suite?tab=readme-ov-file#keypad-test)

- [x] IBM Logo
- [x] Keypad test
- [ ] Buzzer test
- [x] Delay timer test
- [x] Instruction tests
- [ ] Extended instructions (Super-Chip)
- [x] Miscellaneous behavior

## Notes

### Keyboard Layout Mapping

The CHIP-8 uses a 16-key hexadecimal keypad, which is mapped to your host keyboard as follows:

```
CHIP-8:      Host Keyboard:

1 2 3 C      1 2 3 4
4 5 6 D      Q W E R
7 8 9 E      A S D F
A 0 B F      Z X C V
```

- The display uses SDL2 and is scaled for visibility.
- Debugger UI (step, breakpoints, watch) is in progress.
