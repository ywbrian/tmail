#ifndef TMAIL_SECURITY_H
#define TMAIL_SECURITY_H

#include <stddef.h>

int get_machine_key(char *key_output, size_t key_size);
int encrypt_data(const char *data, const char *key, char *output,
        size_t output_size);
int decrypt_data(const char *data, const char *key, char *output,
        size_t output_size);

#endif // TMAIL_SECURITY_H
