#include "utils.h"

#include <stdio.h>
#include <stdarg.h>

/* Console messages */

/**
 * Print a given string to a stream with the "tmail: " prefix
 *
 * Parameters:
 *  stream - The output stream
 *  fmt    - The string format specifiers
 *  ...    - The arguments corresponding to the format specifiers
 *
 * Return:
 *  None
 */
void print_with_prefix(FILE *stream, const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);

    fputs("tmail: ", stream);
    vfprintf(stream, fmt, args);
    fflush(stream);

    va_end(args);
}
