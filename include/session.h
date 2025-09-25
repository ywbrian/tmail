#ifndef TMAIL_SESSION_H
#define TMAIL_SESSION_H

#include "constants.h"

#include <stdbool.h>
#include <time.h>

enum {
    MAX_TOKEN_LENGTH = 512,
    MAX_PROVIDER_LENGTH = 32
};


// Session information structure
// TODO: consider implementing OAuth2 verification
typedef struct {
	char email[MAX_EMAIL_ADDRESS_LENGTH];   // User email address
    char provider[MAX_PROVIDER_LENGTH];     // Name of email service provider
    char access_token[MAX_TOKEN_LENGTH];    // Token for API/IMAP/SMTP
    char refresh_token[MAX_TOKEN_LENGTH];   // Token to refresh access token
    time_t access_token_expiry;             // Time of access token expiry
	time_t last_activity;                   // Local session tracking
	int session_timeout_seconds;            // Local session auto-timeout
} session_t;

bool is_session_valid(void);
bool save_session(session_t *session);
bool load_session(session_t *session);
bool refresh_session(void);
bool clear_session(void);
char *get_current_user_email(void);

#endif // SESSION_H
