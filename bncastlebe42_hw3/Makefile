all: kernel.elf

kernel.elf: kernel.o init.o queue.o process.o process_asm.o boot.o progress.o libos.a
	aarch64-linux-gnu-ld -g -N -Ttext=0x10000 -o kernel.elf kernel.o init.o queue.o process.o process_asm.o boot.o progress.o libos.a

kernel.o: kernel.c
	aarch64-linux-gnu-gcc -g -pedantic -Wall -Wextra -fPIC -std=gnu2x -MMD -c kernel.c -o kernel.o

boot.o: boot.S
	aarch64-linux-gnu-gcc -g -MMD -c boot.S -o boot.o

init.o: init.c libos.h pcb.h stack.h queue.h
	aarch64-linux-gnu-gcc -g -pedantic -Wall -Wextra -fPIC -std=gnu2x -MMD -c init.c -o init.o

queue.o: queue.c queue.h pcb.h
	aarch64-linux-gnu-gcc -g -pedantic -Wall -Wextra -fPIC -std=gnu2x -MMD -c queue.c -o queue.o

process.o: process.c process.h queue.h pcb.h stack.h
	aarch64-linux-gnu-gcc -g -pedantic -Wall -Wextra -fPIC -std=gnu2x -MMD -c process.c -o process.o

process_asm.o: process_asm.S
	aarch64-linux-gnu-gcc -g -MMD -c process_asm.S -o process_asm.o

progress.o: progress.S
	aarch64-linux-gnu-gcc -g -MMD -c progress.S -o progress.o

clean:
	rm -f *.o *.d kernel.elf

-include *.d

run: kernel.elf
	qemu-system-aarch64 -machine raspi3b -kernel kernel.elf

debug: kernel.elf
	qemu-system-aarch64 -machine raspi3b -S -s -kernel kernel.elf &
	ddd --debugger 'gdb-multiarch -ex "target remote localhost:1234" -ex "break main" -ex "continue"' kernel.elf
