#include "session.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <openssl/rand.h>
#include <pwd.h>
#include <stdbool.h>

/* Session constants */
#define SESSION_TOKEN_LENGTH 65             // 64 chars + null terminator
#define SESSION_FILE_PATH ".tmail/session"  // File path to store session info
#define SESSION_TIMEOUT_SECONDS 3600        // 1 hour
#define DEFAULT_FILE_PERMISSIONS            // mkdir for .tmail


static char session_file_path[512];

/**
 * Helper function to retrieve full path to ~/.tmail/session
 *
 * Parameters:
 *  None
 *
 * Return:
 *  None
 */
static void get_session_file_path(void) {
    // Return if path already retrieved
    if (session_file_path[0] != '\0') { return; }

    const char *home = getenv("HOME");
    if (!home) {
        struct passwd *pw = getpwuid(getuid());
        if (!pw) { exit(1); }
        home = pw->pw_dir;
    }

    snprintf(session_file_path, sizeof(session_file_path),
            "%s/.tmail/session", home);

    // Ensure directory exists
    char dir_path[512];
    snprintf(dir_path, sizeof(dir_path), "%s/.tmail", home);
    mkdir(dir_path, 0700); // Ignore error if already exists
}

/**
 * Generate random token as hex string
 *
 * Parameters:
 *  token_str - The string buffer to store the token
 *  len - The size of the token buffer
 *
 * Return:
 *  true if the token was successfully generated, false otherwise
 */
bool generate_session_token(char *token_str, size_t len) {
    if (len < SESSION_TOKEN_LENGTH) { return false; }

    unsigned char buf[32];
    if (RAND_bytes(buf, sizeof(buf)) != 1) { return false; }

    size_t offset = 0;
    for (int i = 0; i < 32; i++) {
        int written = 
            snprintf(token_str + offset, len - offset, "%02x", buf[i]);

        // Encoding failed or buffer too small
        if (written < 0 || written >= (int)(len - offset)) { return false; }

        offset += written;
    }
    token_str[64] = '\0';
    return true;
}


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
    return false;
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
    return false;
}
