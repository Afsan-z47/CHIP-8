# CHIP-8 Emulator (C)

A Chip-8 emulator written in C with built-in debugger support.

[![OpenSSF Best Practices](https://www.bestpractices.dev/projects/11080/badge)](https://www.bestpractices.dev/projects/11080)

## Features

- Full Chip-8 instruction set
- Debugger: step, breakpoints, inspect memory/registers
- Keyboard input
- Load ROMs for testing
- Texture based graphics rendering with SDL2
- Provided option for customizations
- Pixel Coloring
- Resizable windows

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
Running 
```sh
./chip8
```
will show the following help instructions:

```sh
Usage: ./chip8 [options]
  -r <file>  -> rom <file>        ROM file to load
  -d 	     -> debug             Enable debugger
  -a <file>  -> audio <file.wav>  Audio file
  -c <n>     -> color <value>     Set Pixel Color
  Values for <n> is [RED] [BLUE] [GREEN] [YELLOW] [CYAN] [MAGENTA] [WHITE](default) 
  -h 	     -> help              Show this help
  ==============================================
  Ambiguous instruction flags
  -S 	     -> Shift VY instead of Vx for [8XY6] and [8XYE]
  -F 	     -> Change value of I for [FX55] and [FX56]
  -J 	     -> Use VX instead of V0 for [BNNN]
  -D 	     -> Stop CPU when rendering DISPLAY
  -V 	     -> AND[8xy1], OR[8xy2], XOR[8xy3] resets VF to zero
  -O 	     -> Original CHIP-8 behaviour
```
These flags can be put anywhere.

Be carefule with -r and -a . Always follow up with a <file> here. Also follow up -c with a color.
e.g:
```sh
./chip8 -a beep.wab -r roms/your_rom.ch8 -c RED
```


The Modern implementaion is set as default. Its run as:
```sh
./chip8 -a beep.wav -r roms/Tests/5-quirks.ch8 
```
Original CHIP-8 behaviour is run as:
```sh
./chip8 -a beep.wav -r roms/Tests/5-quirks.ch8 -O
```

| <img src="https://github.com/user-attachments/assets/84d64142-2da8-493a-b494-6f2a0aa6a36d" width="95%"> | <img src="https://github.com/user-attachments/assets/d77ea0a3-0dc1-4eac-a084-51ced312f0e1" width="95%"> |
|:--:|:--:|
| **MODERN** | **ORIGINAL** |

Modern will most likely run the common ch8 roms. If not try the Ambigious Instruction flags or the Original CHIP-8 with -O.

Colors can be set using both predefined names
```sh
./chip8 -a beep.wav -c RED roms/your_rom.ch8
```
OR using RGBA COLOR codes
```sh
./chip8 -a beep.wav -c 0XF21ADBB roms/your_rom.ch8
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
- [ ] POSIX support
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
