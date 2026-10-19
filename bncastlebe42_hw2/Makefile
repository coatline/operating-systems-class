all: kernel.elf

kernel.elf: kernel.o boot.o progress.o libos.a
	aarch64-linux-gnu-ld -g -N -Ttext=0x10000 -o kernel.elf kernel.o boot.o progress.o libos.a

kernel.o: kernel.c
	aarch64-linux-gnu-gcc -g -pedantic -Wall -Wextra -fPIC -std=gnu2x -MMD -c kernel.c -o kernel.o

boot.o: boot.S
	aarch64-linux-gnu-gcc -g -MMD -c boot.S -o boot.o

progress.o: progress.S
	aarch64-linux-gnu-gcc -g -MMD -c progress.S -o progress.o

clean:
	rm -f *.o *.d kernel.elf

run: kernel.elf
	qemu-system-aarch64 -machine raspi3b -kernel kernel.elf

debug: kernel.elf
	qemu-system-aarch64 -machine raspi3b -S -s -kernel kernel.elf &
	ddd --debugger 'gdb-multiarch -ex "target remote localhost:1234" -ex "break main" -ex "continue"' kernel.elf