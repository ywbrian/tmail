#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>

#define xstr(s) str(s)
#define str(s) #s

/* Function declarations */
bool parse_args(int argc, const char **argv);

void print_help(void);
void print_version(void);

#endif // UTILS_H
