#ifndef _X86_64_PORT_H
#define _X86_64_PORT_H

#include <stdint.h>

inline unsigned char inb(uint16_t port)
{
    unsigned char ret;
    asm volatile("in %%dx, %%al" : "=a"(ret) : "d"(port) : "memory");
    return ret;
}

inline void outb(uint16_t port, uint8_t value)
{
    asm volatile("out %%al, %%dx" : : "a"(value), "d"(port) : "memory");
}

#endif
