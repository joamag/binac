all: loader.o kernel.o common.o linker.ld
	ld -T linker.ld -o kernel.bin loader.o kernel.o common.o -melf_i386

loader.o: loader.asm
	nasm -f elf -o loader.o loader.asm

kernel.o: kernel.c
	gcc -o kernel.o -c kernel.c -Wall -Wextra -nostdlib -nostartfiles -nodefaultlibs -m32

common.o: common.c
	gcc -o common.o -c common.c -Wall -Wextra -nostdlib -nostartfiles -nodefaultlibs -m32

clean:
	rm -f loader.o kernel.o

run: kernel.bin
	qemu -kernel kernel.bin
