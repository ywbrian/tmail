#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>
#include <stddef.h>

#define UNUSED(x) (void)(x)

#define xstr(s) str(s)
#define str(s) #s

bool parse_args(int argc, const char **argv);

/* Console messages */
void print_help(void);
void print_version(void);

/* Cryptography tools */
bool get_machine_key(char *key_output, size_t key_size);
bool encrypt_data(const char *data, const char *key, char *output,
        size_t output_size);
bool decrypt_data(const char *data, const char *key, char *output,
        size_t output_size);

#endif // UTILS_H
