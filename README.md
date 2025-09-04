<h1>CHIP-8 Emulator (C)</h1>

<p>
A <strong>Chip-8 emulator</strong> written in C with built-in debugger support.
</p>

[![OpenSSF Best Practices](https://www.bestpractices.dev/projects/11080/badge)](https://www.bestpractices.dev/projects/11080)

| <img src="https://github.com/user-attachments/assets/e660f2ec-2bdc-4133-990e-97bdd3d6c9aa" alt="IBM Test Logo" width="400"/> | <img src="https://github.com/user-attachments/assets/3a6db82d-834c-4944-86b9-c19424ae63b3" alt="Second Screenshot" width="400"/> |
|:---:|:---:|


---

## 📖 Table of Contents
- [Features](#-features)
- [Build & Installation](https://github.com/Afsan-z47/CHIP-8/blob/main/README.md#%EF%B8%8F-build--installation)
- [Run](https://github.com/Afsan-z47/CHIP-8/blob/main/README.md#%EF%B8%8F-build--installation)
- [Screenshots](#-screenshots)
- [Test Status](#-test-status)
- [Notes](#-notes)
- [Roadmap](#-roadmap)
- [Contributing](#-contributing)
- [License](#-license)

---

## ✨ Features
- Full Chip-8 instruction set
- Built-in debugger (step, breakpoints, inspect memory/registers)
- SDL2 display (texture-based rendering) with resizable windows
- GPU rendering with CPU fallback
- Keyboard input with customizable key mapping
- Monochrome pixel color selector
- Support for **Legacy CHIP-8** and **Modern CHIP-8**
- Ambiguous opcode selection
- Safety ensured using compiler hardening

---

## ⚙️ Build & Installation

Run these instructions in the CHIP-8 directory:

### Build
```sh
make
````

### Rigorous Testing

```sh
make debug
```

Includes additional tests from
[Compiler Hardening Guidelines](https://best.openssf.org/Compiler-Hardening-Guides/Compiler-Options-Hardening-Guide-for-C-and-C++.html)

### Clean Up

```sh
make clean
```

---

## ▶️ Run

Run without options:

```sh
./chip8
```
will show the following help:
```sh
Usage: ./chip8 [options]
  -r <file>  -> rom <file>        ROM file to load
  -d 	     -> debug             Enable debugger
  -a <file>  -> audio <file.wav>  Audio file
  -k 	     -> Customize Keyboard
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
  Using other ambigious instruction flags with "-O" will flip the optins
```
Too simply run use:
```sh
./chip8 -r <path_to_your_rom.ch8>
```

A more customiable command will look like this:
```sh
./chip8 -a <audio_file> -r <path_to_your_rom.ch8> -c <color> -h[help] -SFJDV[Alike ambiguous instruction flags] -k[this ones for keyboard]
```

### Examples

**Run with audio (default: `beep.wav`):**

```sh
./chip8 -a beep.wav -r roms/Tests/2-ibm-logo.ch8
```

**Run in Modern mode (default):**

```sh
./chip8 -r roms/Tests/5-quirks.ch8
```

**Run in Legacy mode:**

```sh
./chip8 -r roms/Tests/5-quirks.ch8 -O
```

---

## 🖼️ Screenshots
These had [ -c Yellow ] flags added

| <img src="https://github.com/user-attachments/assets/5b2d2d4b-7d62-4603-88de-d93891b9c555" alt="Legacy CHIP-8" width="400"/> | <img src="https://github.com/user-attachments/assets/020e2f7a-0f3b-4362-8f99-d0fa6a0cc7a1" alt="Modern CHIP-8" width="400"/> |
| :--------------------------------------------------------------------------------------------------------------------------: | :--------------------------------------------------------------------------------------------------------------------------: |
|                                                       **Legacy CHIP-8**                                                      |                                                       **Modern CHIP-8**                                                      |

---

## ✅ Test Status

Test ROMs from Timendus’ [Chip-8 Test Suite](https://github.com/Timendus/chip8-test-suite?tab=readme-ov-file#keypad-test)

* [x] IBM Logo
* [x] Keypad test
* [x] Buzzer test
* [x] Delay timer test
* [x] Instruction tests
* [ ] Super-CHIP
* [ ] XO-CHIP
* [ ] Debugger
* [x] Miscellaneous behavior
* [x] Complete test → Timendus CHIP-8 Test Suite

---

## 📝 Notes

### Keyboard Layout Mapping

The CHIP-8 uses a 16-key hexadecimal keypad, mapped to your host keyboard as:

```
CHIP-8:      Host Keyboard:

1 2 3 C      1 2 3 4
4 5 6 D      Q W E R
7 8 9 E      A S D F
A 0 B F      Z X C V
```

* The display uses SDL2 and is scaled for visibility.
* Debugger UI (step, breakpoints, watch) is in progress.

---

## 🚀 Idea board

Ideas to be implemented

* [ ] JIT
* [ ] Super-CHIP support
* [ ] XO-CHIP support

---

## 🤝 Contributing

Contributions are welcome!
Feel free to open issues, submit PRs. Please do not suggest improvements but if you have one implemented make a pull request. We will review it and accept it.

---

## 📜 License

This project is licensed under the **MIT License**.
See the [LICENSE](LICENSE) file for details.
