# CHIP-8 Emulator (C)

A Chip-8 emulator written in C with built-in debugger support.

[![OpenSSF Best Practices](https://www.bestpractices.dev/projects/11080/badge)](https://www.bestpractices.dev/projects/11080)

## Features

- Full Chip-8 instruction set
- Debugger: step, breakpoints, inspect memory/registers
- SDL2 display [Texture based rendering] with resizable windows
- Supports GPU rendering with CPU fallback
- Keyboard input
- Customizable Keyboard
- Monochrome pixel color selector
- Support for Legacy CHIP-8
- Support for Modern CHIP-8
- Supports ambigious opcode selection.
- Safety ensured using compiler hardening.

## Compile

Run these instrictions in the CHIP-8 directory
### Build
```sh
make 
```
### Rigorous Testing
```sh
make debug
```
- [x] Additonal tests are added from [Compiler Hardening](https://best.openssf.org/Compiler-Hardening-Guides/Compiler-Options-Hardening-Guide-for-C-and-C++.html)
### clean up
```sh
make clean
```
## Run

```sh
./chip8 beep.wav roms/your_rom.ch8
```

## Test Status

Test ROMs from Timendus' [Chip-8 test suite](https://github.com/Timendus/chip8-test-suite?tab=readme-ov-file#keypad-test)

- [x] IBM Logo
- [x] Keypad test
- [x] Buzzer test
- [x] Delay timer test
- [x] Instruction tests
- [ ] Super-CHIP
- [ ] XO-CHIP
- [ ] Debugger
- [x] Miscellaneous behavior
- [x] Complete test -> Timendus CHIP-8 Testsuite
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
