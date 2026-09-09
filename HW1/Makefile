# Cross compiler
CC      := aarch64-linux-gnu-gcc
# Assembler executable
AS      := aarch64-linux-gnu-gcc
# Linker
LD      := aarch64-linux-gnu-gcc
# Emulator executable to boot the compiled os kernal
EMU     := qemu-system-aarch64

# Added -I../ so the compiler finds headers in the parent directory
CFLAGS  := -Wall -Wextra -std=c99 -I../
ASFLAGS := 

all: kernel.elf

kernel.elf: kernel.o boot.o progress.o libos.a
	$(LD) kernel.o boot.o progress.o libos.a -o $@

kernel.o: kernel.c
	$(CC) $(CFLAGS) -c $< -o $@

boot.o: boot.S
	$(AS) $(ASFLAGS) -c $< -o $@

progress.o: progress.S
	$(AS) $(ASFLAGS) -c $< -o $@

libos.a:

clean:
	rm -f kernel.o boot.o progress.o kernel.elf

.PHONY: all clean