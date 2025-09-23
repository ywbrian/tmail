#ifndef CONSTANTS_H
#define CONSTANTS_H

#define MAX_EMAIL_ADDRESS_LENGTH 255    // 254 chars + null terminator
#define CONFIG_PATH_BUFFER_SIZE 512     // Buffer size for config path

/* Session constants */
#define SESSION_TOKEN_LENGTH 65         // 64 chars + null terminator
#define SESSION_FILE_PATH ".tmail/session"
#define DEFAULT_SESSION_TIMEOUT 86400   // 24 hours in seconds

/* Cryptography constants */
#define MACHINE_KEY_LENGTH 65   // 64 hex chars + null terminator
#define AES_KEY_SIZE 32         // 256-bit AES key
#define AES_IV_SIZE 16          // AES block size for IV
#define AES_IV_HEX_LENGTH 32    // IV in hex (16 * 2)

#define PLAINTEXT_DATA_BUFFER_SIZE 128 // Max plaintext data length
#define ENCRYPTED_DATA_BUFFER_SIZE 512 // Max encrypted data length

// Flag parsing exit codes
typedef enum {
    PARSE_CONTINUE = -1,    // Continue normal execution
    PARSE_EXIT_SUCCESS = 0, // Exit with success
    PARSE_EXIT_ERROR = 1    // Exit with error
} parse_result_t;

#endif // CONSTANTS_H
