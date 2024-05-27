#include <kernel/hcf.h>
#include <kernel/tty.h>
#include <stdio.h>

void kmain(void) {
	printf("Hello, World\n");
	hcf();
}