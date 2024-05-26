#include <stdio.h>

#include <kernel/tty.h>

/**
 * Called before global constructors
 * 
 * Should set up terminal and heap
 */
void kernel_early_main() {
	terminal_initialize();
}

/*
 * Called after global constructors
 */
void kernel_main(void) {
	printf("Hello, kernel World!\n%x", kernel_main);
}
