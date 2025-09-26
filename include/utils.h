#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdbool.h>

#define UNUSED(x) (void)(x)

#define xstr(s) str(s)
#define str(s) #s

bool validate_email(const char *email);

/* Console messages */
void print_with_prefix(FILE *stream, const char *fmt, ...);

#endif // UTILS_H
