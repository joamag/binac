all: loader.o kernel.o linker.ld
	ld -T linker.ld -o kernel.bin loader.o kernel.o -melf_i386

loader.o: loader.asm
	nasm -f elf -o loader.o loader.asm

kernel.o: kernel.c
	gcc -o kernel.o -c kernel.c -Wall -Wextra -nostdlib -nostartfiles -nodefaultlibs -m32

clean:
	rm -f loader.o kernel.o

run: kernel.bin
	qemu -kernel kernel.bin
