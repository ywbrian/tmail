#ifndef TMAIL_SESSION_H
#define TMAIL_SESSION_H

#include "constants.h"

#include <stdbool.h>
#include <time.h>

// Session information structure
typedef struct {
	char email[MAX_EMAIL_ADDRESS_LENGTH];           // User email address
    esp_t provider;             // Name of email service provider
    char encrypted_password[MAX_PASSWORD_LENGTH];   // Encrypted app password
	time_t last_activity;                           // Local session tracking
	int session_timeout_seconds;                    // Local session auto-timeout
} session_t;

bool is_session_valid(void);
bool save_session(session_t *session);
bool load_session(session_t *session);
bool refresh_session(void);
bool clear_session(void);
char *get_current_user_email(void);

#endif // SESSION_H
