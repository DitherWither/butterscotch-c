global _long_mode_start
extern kernel_main

section .text
bits 64
_long_mode_start:
    ; load 0 into all data segment registers
    mov ax, 0
    mov ss, ax
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    
    call kernel_main

    cli
    hlt