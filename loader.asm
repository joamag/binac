global loader                           ; making entry point visible to linker
extern kmain                            ; kmain is defined elsewhere

                                        ; setting up the multiboot header, see grub docs for details
MODULEALIGN equ  1 << 0                 ; align loaded modules on page boundaries
MEMINFO     equ  1 << 1                 ; provide memory map
FLAGS       equ  MODULEALIGN | MEMINFO  ; this is the Multiboot "flag" field
MAGIC       equ  0x1badb002             ; "magic number" lets bootloader find the header
CHECKSUM    equ -(MAGIC + FLAGS)        ; checksum required

section .text
align 4
MultiBootHeader:
    dd MAGIC
    dd FLAGS
    dd CHECKSUM

                                       ; reserve initial kernel stack space
STACKSIZE equ 0x4000                   ; that's 16k

loader:
    mov esp, stack + STACKSIZE         ; set up the stack
    push eax                           ; pass multiboot magic number
    push ebx                           ; pass multiboot info structure
    call  kmain                        ; call kernel proper
    cli
hang:
    hlt                                ; halt machine should kernel return
    jmp   hang

section .bss
align 4
stack:
   resb STACKSIZE                     ; reserve 16k stack on a doubleword boundary
