#include "common.h"

void outb(u16int port, u8int value) {
    asm volatile ("outb %1, %0" : : "dN" (port), "a" (value));
}

u8int inb(u16int port) {
    /* allocates the return value */
    u8int return_value;

    /* calls the assembly code */
    asm volatile ("inb %1, %0" : "=a" (return_value) : "dN" (port));

    /* returns the return value */
    return return_value;
}

u16int inw(u16int port) {
    /* allocates the return value */
    u16int return_value;

    /* calls the assembly code */
    asm volatile ("inw %1, %0" : "=a" (return_value) : "dN" (port));

    /* returns the return value */
    return return_value;
}
