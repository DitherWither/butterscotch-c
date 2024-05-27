#ifndef _QEMU_DEBUGCON_H
#define _QEMU_DEBUGCON_H

#include "port.h"
#include <stddef.h>

#define QEMU_DEBUGCON_PORT 0xe9

inline void qemu_debugcon_putchar(char c) {
    outb(QEMU_DEBUGCON_PORT, c);
}

inline void qemu_debugcon_write(const char* data, size_t size) {
    for (size_t i = 0; i < size; i++) {
        qemu_debugcon_putchar(data[i]);
    }
}

#endif