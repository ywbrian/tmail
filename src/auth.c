#include "auth.h"
#include "security.h"
#include "session.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <curl/curl.h>

#define __STDC_WANT_LIB_EXT1__ 1

int authenticate_email(esp_t esp, const char *email) {
    switch(esp) {
        case ESP_GMAIL:
            authenticate_gmail(email);
            break;
        case ESP_OUTLOOK:
        case ESP_YAHOO:
        case ESP_ICLOUD:
        case ESP_OTHER:
            fprintf(stderr, "Provider not yet supported");
            return 1;
        case ESP_INVALID:
        default:
            return 1;
    }
    return 1;
}

int authenticate_gmail(const char *email) {
    printf("Gmail requires an app-specific password for CLI access.\n");
    printf("Please do the following:\n");
    printf("1. Enable 2-Step Verification in Gmail\n");
    printf("2. Go to Security -> App passwords\n");
    printf("3. Generate a password for 'Mail'\n");
    printf("4. Enter that password below\n\n");

    char password[MAX_PASSWORD_LENGTH];
    printf("App password: ");
    if (read_password(password, sizeof(password)) != 0) {
        fprintf(stderr, "Failed to read password\n");
        return 1;
    }
    session_t session = {0};
    if (!test_gmail_imap_connection(email, password, &session)) {
        fprintf(stderr, "Authentication failed. Check your email and password\n");
        // Clear password from memory
        memset_s(password, sizeof(password), 0, sizeof(password));
    return 1;
}

char machine_key[MACHINE_KEY_LENGTH];
if (get_machine_key(machine_key, sizeof(machine_key)) != 0) {
    fprintf(stderr, "Failed to generate encryption key\n");
    memset_s(password, sizeof(password), 0, sizeof(password));
    return 1;
}

if (encrypt_data(password, machine_key, session.encrypted_password,
            sizeof(session.encrypted_password)) != 0) {
    fprintf(stderr, "Failed to encrypt password\n");
    memset_s(password, sizeof(password), 0, sizeof(password));
    return 1;
}

    // Erase password from memory
    memset_s(password, sizeof(password), 0, sizeof(password));

    session.last_activity = time(NULL);
    session.session_timeout_seconds = 86400;    // Seconds in a day

    if (!save_session(&session)) {
        fprintf(stderr, "Failed to save session!\n");
        return 1;
    }

    printf("Login successful\n");
    return 0;
}

bool test_gmail_imap_connection(const char *email, const char *password,
        session_t *session) {
    CURL *curl = curl_easy_init();
    if (!curl) { return false; }

    curl_easy_setopt(curl, CURLOPT_URL, "imaps://imap.gmail.com:993");
    curl_easy_setopt(curl, CURLOPT_USERNAME, email);
    curl_easy_setopt(curl, CURLOPT_PASSWORD, password);
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "EXAMINE INBOX");

    CURLcode res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);

    if (res != CURLE_OK) { return false; }

    // Store credentials in session
    strncpy(session->email, email, sizeof(session->email) - 1);
    session->provider = ESP_GMAIL;

    return true;
}

int read_password(char *password, size_t size) {
    struct termios old, new;

    // Disable echo
    tcgetattr(STDIN_FILENO, &old);
    new = old;
    new.c_lflag &= ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &new);

    // Read password
    if (fgets(password, size, stdin) == NULL) {
        tcsetattr(STDIN_FILENO, TCSANOW, &old);
        return 1;
    }

    // Restore echo
    tcsetattr(STDIN_FILENO, TCSANOW, &old);
    printf("\n");

    // Remove newline if any
    password[strcspn(password, "\n")] = '\0';
    return 0;
}

esp_t prompt_for_esp(void) {
    printf("Select your email service provider:\n");
    printf("    1) Gmail\n");
    printf("    2) Outlook/Hotmail\n");
    printf("    3) Yahoo\n");
    printf("    4) iCloud\n");
    printf("    5) Custom/Other\n");
    printf("> ");

    char input[10];
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Failed to read input\n");
        return ESP_INVALID;
    }

    char *endptr;
    int choice = strtol(input, &endptr, 10);
    if ((*endptr != '\n' && *endptr != '\0') || choice < 1 || choice > 5) {
        fprintf(stderr, "Invalid selection: %d\n", choice);
        return ESP_INVALID;
    }

    return (esp_t)choice;
}
