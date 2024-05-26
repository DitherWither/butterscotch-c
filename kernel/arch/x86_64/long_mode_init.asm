global _long_mode_start
extern _init
extern _fini
extern kernel_early_main
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
    
    call kernel_early_main
    call _init
    call kernel_main
    call _fini

    cli
    hlt