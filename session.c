#include "session.h"
#include "constants.h"
#include "utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/stat.h>

#define CONFIG_FILE ".tmail_config"

/**
 * Check if there is currently a valid session
 *
 * Parameters:
 *  none
 *
 * Returns:
 *  true if the session is valid, false otherwise
 */
bool is_session_valid(void) {
    const char *home = getenv("HOME");
    if (!home) { return false; }

    char config_path[CONFIG_PATH_BUFFER_SIZE];
    snprintf(config_path, sizeof(config_path), "%s/%s", home, CONFIG_FILE);

    // Read from config file
    FILE *f = fopen(config_path, "rb");
    if (!f) { return false; }

    session_t session;
    if (fread(&session, sizeof(session), 1, f) != 1) {
        fclose(f);
        return false;
    }
    fclose(f);

    return true;
}

/**
 * Save a session to the program configuration file
 *
 * Parameters:
 *  email: the email address to save
 *  password: the password to be encrypted and saved
 *
 * Return:
 *  true if saving succeeded, false otherwise
 */
bool save_session(const char *email, const char *password) {
    // Get machine key
    char machine_key[MACHINE_KEY_LENGTH];
    if (!get_machine_key(machine_key, sizeof(machine_key))) { return false; }

    // Encrypt password using machine key
    char encrypted_password[ENCRYPTED_DATA_BUFFER_SIZE];
    if (!encrypt_data(password, machine_key, encrypted_password,
                sizeof(encrypted_password))) {
        return false;
    }

    session_t session = {0};

    strncpy(session.email, email, MAX_EMAIL_ADDRESS_LENGTH -1);
    session.email[MAX_EMAIL_ADDRESS_LENGTH - 1] = '\0';

    strncpy(session.encrypted_password, encrypted_password, 
            ENCRYPTED_DATA_BUFFER_SIZE - 1);
    session.encrypted_password[ENCRYPTED_DATA_BUFFER_SIZE - 1] = '\0';

    // Set timestamps
    session.last_activity = time(NULL);
    session.session_timeout_seconds = DEFAULT_SESSION_TIMEOUT;

    const char *home = getenv("HOME");
    if (!home) {
        return false;
    }

    char config_path[CONFIG_PATH_BUFFER_SIZE];
    snprintf(config_path, sizeof(config_path), "%s/%s", home, CONFIG_FILE);

    // Write session to file (binary)
    FILE *f = fopen(config_path, "wb");
    if (!f) { return false; }

    bool success = (fwrite(&session, sizeof(session), 1, f) == 1);
    fclose(f);

    // Set restrictive permissions (user read/write only)
    chmod(config_path, 0600);

    return success;
}
