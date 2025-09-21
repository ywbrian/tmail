#include "constants.h"
#include "utils.h"

#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {
#if 0
	if (parse_global_flags(argc, (const char **)argv) == 0) {
		return 0;
	}

	if (!parse_args(argc, (const char **)(argv))) {
		return 0;
	}
#endif

    char machine_key[MACHINE_KEY_LENGTH];
    if (!get_machine_key(machine_key, sizeof(machine_key))) {
        return 1;
    }
    printf("Machine key %.16s...\n", machine_key);

    const char* test_password = "password123";
    char encrypted[ENCRYPTED_DATA_BUFFER_SIZE];
    char decrypted[PLAINTEXT_DATA_BUFFER_SIZE];

    if (!encrypt_data(test_password, machine_key, encrypted, 
                sizeof(encrypted))) {
        printf("Encryption failed\n");
        return 1;
    }
    printf("Encrypted: %.32s...\n", encrypted);

    if (!decrypt_data(encrypted, machine_key, decrypted, sizeof(decrypted))) {
        printf("Decryption failed\n");
        return 1;
    }
    printf("Decrypted: %s\n", decrypted);
    
    if (strcmp(test_password, decrypted) == 0) {
        printf("Encryption/decryption test PASSED\n");
    } else {
        printf("Encryption/decryption test FAILED\n");
        return 1;
    }

	return 0;
}
