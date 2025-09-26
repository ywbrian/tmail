#ifndef TMAIL_CONSTANTS_H
#define TMAIL_CONSTANTS_H

#define MAX_EMAIL_ADDRESS_LENGTH 255    // 254 chars + null terminator
#define MAX_PASSWORD_LENGTH 512
#define MAX_PATH_LENGTH 512             // Maximum length of path string
#define MAX_URL_LENGTH 512

#define MACHINE_KEY_LENGTH 65   // 64 hex chars + null terminator

/* Email service providers */
typedef enum {
    ESP_INVALID = -1,
    ESP_GMAIL = 1,
    ESP_OUTLOOK,
    ESP_YAHOO,
    ESP_ICLOUD,
    ESP_OTHER
} esp_t;

// Flag parsing exit codes
typedef enum {
    PARSE_CONTINUE = -1,    // Continue normal execution
    PARSE_EXIT_SUCCESS = 0, // Exit with success
    PARSE_EXIT_ERROR = 1    // Exit with error
} parse_result_t;

#endif // TMAIL_CONSTANTS_H
