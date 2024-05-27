#include "../kernel/kernel.h"
#include "kernel/tty.h"
#include <limine.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Set the base revision to 2, this is recommended as this is the latest
// base revision described by the Limine boot protocol specification.
// See specification for further info.

__attribute__((used,
               section(".requests"))) static volatile LIMINE_BASE_REVISION(2);

__attribute__((used,
               section(".requests_start_"
                       "marker"))) static volatile LIMINE_REQUESTS_START_MARKER;

__attribute__((
    used,
    section(
        ".requests_end_marker"))) static volatile LIMINE_REQUESTS_END_MARKER;


/*
 * Performs early initialization and passes control over to kmain
 */
void _start() {
    // Ensure the bootloader actually understands our base revision (see spec).
    if (LIMINE_BASE_REVISION_SUPPORTED == false) {
        abort();
    }

    terminal_initialize();

    kmain();

    printf("kmain() exited\n");
    abort();
}