#ifndef CONSTANTS_H
#define CONSTANTS_H

#define MAX_EMAIL_ADDRESS_LENGTH 255    // 254 chars + null terminator
#define CONFIG_PATH_BUFFER_SIZE 512     // Buffer size for config path
#define MAX_PATH_LENGTH 512             // Maximum length of path string

#define PLAINTEXT_DATA_BUFFER_SIZE 128 // Max plaintext data length
#define ENCRYPTED_DATA_BUFFER_SIZE 512 // Max encrypted data length

// Flag parsing exit codes
typedef enum {
    PARSE_CONTINUE = -1,    // Continue normal execution
    PARSE_EXIT_SUCCESS = 0, // Exit with success
    PARSE_EXIT_ERROR = 1    // Exit with error
} parse_result_t;

#endif // CONSTANTS_H
