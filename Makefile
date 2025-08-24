CC      := gcc
SRC     := src/main.c src/display.c src/chip8.c src/input.c src/audio.c
BIN     := chip8
LIBS    := -lSDL2 -lSDL2_mixer

# Hardening & sanitizers for debug only
HARDEN  := -Wall -Wextra -Wpedantic \
           -Wformat -Wformat=2 -Wconversion -Wimplicit-fallthrough \
           -Werror=format-security -Werror=implicit-function-declaration \
           -Wtrampolines -Wl,--fatal-warnings \
           -U_FORTIFY_SOURCE -D_FORTIFY_SOURCE=3 \
           -D_GLIBCXX_ASSERTIONS \
           -fstrict-flex-arrays=3 \
           -fstack-clash-protection -fstack-protector-strong \
           -fPIE -pie \
           -fcf-protection=full -fno-plt \
           -fzero-call-used-regs=all -fno-delete-null-pointer-checks \
           -fno-strict-overflow -fno-strict-aliasing -ftrivial-auto-var-init=zero \
           -fexceptions -fasynchronous-unwind-tables \
           -Wl,-z,now -Wl,-z,relro -Wl,-z,noexecstack -Wl,-z,nodlopen \
           -Wl,--as-needed -Wl,--no-copy-dt-needed-entries

SAN     := -fsanitize=address,undefined,leak,signed-integer-overflow,shift,unreachable \
           -fno-omit-frame-pointer

.PHONY: all release debug clean

# Default target = plain GCC release build
all: release

# Plain GCC release (no hardening, no sanitizer)
release:
	$(CC) $(SRC) -o $(BIN) $(LIBS)

# Debug build with all hardening and sanitizers
debug:
	$(CC) $(SRC) -O1 -g3 $(HARDEN) $(SAN) -o $(BIN)-debug $(LIBS)

# Remove binaries
clean:
	rm -f $(BIN) $(BIN)-debug *.o

