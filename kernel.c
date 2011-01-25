void write_string(int colour, const char *string);

void kmain(void* mbd, unsigned int magic) {
    if (magic != 0x2badb002) {
        /* Something went not according to specs. Print an error */
        /* message and halt, but do *not* rely on the multiboot */
        /* data structure. */
    }

    /* You could either use multiboot.h */
    /* (http://www.gnu.org/software/grub/manual/multiboot/multiboot.html#multiboot_002eh) */
    /* or do your offsets yourself. The following is merely an example. */
    char *boot_loader_name = (char*) ((long*) mbd)[16];

    /* writes the hello world string */
    write_string(0x07, "hello world");

    /* Write your kernel here. */
}

 void keyboard_scan() {
    byte new_scan_code = inportb(0x60);
 
    /**
	 * Do something with the scancode.
     * Remember you only get '''one''' byte of the scancode each time the ISR is invoked.
     * (Though most of the times the scancode is only one byte.) 
     */
 
    /* Acknowledge the IRQ, pretty much tells the PIC that we can accept >=priority IRQs now. */
    outportb(0x20, 0x20);
 }

void write_string(int colour, const char *string) {
    /* starts the video buffer value */
    volatile char *video = (volatile char *) 0xB8000;

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
