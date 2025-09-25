#include "session.h"
#include "constants.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <openssl/rand.h>
#include <pwd.h>
#include <stdbool.h>
#include <errno.h>

/* Session constants */
#define SESSION_FILE_PATH ".tmail/session"  // File path to store session info
#define DEFAULT_FILE_PERMISSIONS 0600       // mkdir for .tmail

// Buffer to store session file path during runtime
static char session_file_path[MAX_PATH_LENGTH];

/**
 * Helper function to retrieve full path to ~/.tmail/session
 *
 * Parameters:
 *  None
 *
 * Return:
 *  -1 if already retrieved
 *  1  if retrieval failed
 *  0  if retrieval succeeded
 */
static int get_session_file_path(void) {
    if (session_file_path[0] != '\0') { return -1; }

    const char *home = getenv("HOME");
    if (!home) {
        struct passwd *pw = getpwuid(getuid());
        if (!pw) { return 1; }
        home = pw->pw_dir;
    }

    snprintf(session_file_path, sizeof(session_file_path),
            "%s/%s", home, SESSION_FILE_PATH);

    // Ensure directory exists
    char dir_path[MAX_PATH_LENGTH];
    snprintf(dir_path, sizeof(dir_path), "%s/.tmail", home);

    // Ignore errors where directory already exists
    if(mkdir(dir_path, DEFAULT_FILE_PERMISSIONS) != 0 && errno != EEXIST) {
        perror("mkdir");
        return 1;
    }

    return 0;
}

/**
 * Check if there is currently a valid session
 *
 * Parameters:
 *  None
 *
 * Returns:
 *  True if the session is valid, false otherwise
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
 *  True if saving succeeded, false otherwise
 */
bool save_session(session_t *session) {
    return false;
}
