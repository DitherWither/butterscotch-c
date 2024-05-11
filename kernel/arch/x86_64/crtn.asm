bits 64

section .init
    ; GCC will put the contents of crtend.o's .init section here
    pop rbp
    ret


section .fini
    ; GCC will put the contents of crtend.o's .fini section here
    pop rbp
    ret