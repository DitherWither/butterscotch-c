
#include "flanterm/backends/fb.h"
#include "flanterm/flanterm.h"
#include "qemu_debugcon.h"
#include <kernel/tty.h>
#include <limine.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// TODO make a proper config system
bool debugcon_enable = true;

__attribute__((
    used,
    section(".requests"))) static volatile struct limine_framebuffer_request
    framebuffer_request = {.id = LIMINE_FRAMEBUFFER_REQUEST, .revision = 0};

struct flanterm_context *ft_ctx = NULL;

void terminal_initialize(void) {
    // Ensure we got a framebuffer.
    if (framebuffer_request.response == NULL ||
        framebuffer_request.response->framebuffer_count < 1) {
        abort();
    }

    // Fetch the first framebuffer.
    struct limine_framebuffer *framebuffer =
        framebuffer_request.response->framebuffers[0];

    terminal_writestring("test print");

    ft_ctx = flanterm_fb_init(
        NULL, NULL, framebuffer->address, framebuffer->width,
        framebuffer->height, framebuffer->pitch, framebuffer->red_mask_size,
        framebuffer->red_mask_shift, framebuffer->green_mask_size,
        framebuffer->green_mask_shift, framebuffer->blue_mask_size,
        framebuffer->blue_mask_shift, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
        NULL, 0, 0, 1, 0, 0, 0);
}

void terminal_putchar(char c) {
    if (debugcon_enable) {
        qemu_debugcon_putchar(c);
    }
    if (ft_ctx) {
        flanterm_write(ft_ctx, &c, 1);
    }
}

void terminal_write(const char *data, size_t size) {
    if (debugcon_enable) {
        qemu_debugcon_write(data, size);
    }
    if (ft_ctx) {
        flanterm_write(ft_ctx, data, size);
    }
}

void terminal_writestring(const char *data) {
    terminal_write(data, strlen(data));
}