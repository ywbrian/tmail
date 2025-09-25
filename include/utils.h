#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdbool.h>

#define UNUSED(x) (void)(x)

#define xstr(s) str(s)
#define str(s) #s

/* Console messages */
void print_with_prefix(FILE *stream, const char *fmt, ...);

/* Cryptography tools */
bool get_machine_key(char *key_output, size_t key_size);
bool encrypt_data(const char *data, const char *key, char *output,
        size_t output_size);
bool decrypt_data(const char *data, const char *key, char *output,
        size_t output_size);

#endif // UTILS_H
