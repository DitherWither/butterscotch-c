#ifndef _STDIO_H
#define _STDIO_H 1

#include <stdarg.h>
#include <stddef.h>
#include <sys/cdefs.h>

#define EOF (-1)

#ifdef __cplusplus
extern "C" {
#endif

int printf(const char *restrict format, ...);
int putchar(int);
int puts(const char *);

#ifdef __cplusplus
}
#endif

#endif
