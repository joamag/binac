#include "common.h"

void write_string(s32int colour, const s8int *string);
void move_cursor(u16int cursor_x, u16int cursor_y);
void clear_screen();

void kmain(void *mbd, u32int magic) {
    /* in case the magic is not valid */
    if (magic != 0x2badb002) {
        /* Something went not according to specs. Print an error */
        /* message and halt, but do *not* rely on the multiboot */
        /* data structure. */
    }

    /* You could either use multiboot.h */
    /* (http://www.gnu.org/software/grub/manual/multiboot/multiboot.html#multiboot_002eh) */
    /* or do your offsets yourself. The following is merely an example. */
    s8int *boot_loader_name = (s8int *) ((s32int *) mbd)[16];

    /* clears the screen */
    clear_screen();

    /* writes the hello world string */
    write_string(0x07, "hello world");

    /* Write your kernel here. */
}

 void keyboard_scan() {
    /* reads the new scan code */
    s8int new_scan_code = inb(0x60);

    /**
     * Do something with the scancode.
     * Remember you only get '''one''' byte of the scancode each time the ISR is invoked.
     * (Though most of the times the scancode is only one byte.)
     */

    /* acknowledge the IRQ, pretty much tells the PIC that we can accept >=priority IRQs now */
    outb(0x20, 0x20);
 }

void write_string(s32int colour, const s8int *string) {
    /* starts the video buffer value */
    volatile s8int *video = (volatile s8int *) 0xb8000;

    /* iterates while the end of string is not found */
    while(*string != 0) {
        /* sets the video buffer value as the string value */
        *video = *string;

        /* increments the string buffer */
        string++;

        /* increments the video buffer */
        video++;

        /* sets the video buffer with the colour */
        *video = colour;

        /* increments the video buffer */
        video++;
    }
}

void move_cursor(u16int cursor_x, u16int cursor_y) {
    /* calculates the cursor location */
    u16int cursor_location = cursor_y * 80 + cursor_x;

    /* tells the vga board we are setting the high cursor byte */
    outb(0x3d4, 14);

    /* sends the high cursor byte */
    outb(0x3d5, cursor_location >> 8);

    /* tells the VGA board we are setting the low cursor byte */
    outb(0x3d4, 15);

    /* sends the low cursor byte */
    outb(0x3d5, cursor_location);
}

void clear_screen() {
    /* allocates the index */
    u32int index;

    /* starts the video buffer value */
    volatile s16int *video = (volatile s16int *) 0xb8000;

    /* makes an attribute byte for the default colours */
    u8int attributeByte = (0 << 4) | (15 & 0x0f);
    u16int blank = 0x20 | (attributeByte << 8);

    /* iterates over all the chacter fields in the video buffer */
    for(index = 0; index < 80 * 25; index++) {
        /* sets the blank value */
        video[index] = blank;
    }

    /* moves the cursor to the start */
    move_cursor(0, 0);
}
