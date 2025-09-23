#ifndef SESSION_H
#define SESSION_H

#include "constants.h"

#include <stdbool.h>
#include <time.h>

#define SESSION_TOKEN_LENGTH 65             // 64 chars + null terminator

// Session information structure
// TODO: consider implementing OAuth2 verification
typedef struct {
	char email[MAX_EMAIL_ADDRESS_LENGTH];
    char token[SESSION_TOKEN_LENGTH];       // hex-encoded 32-byte token
	time_t last_activity;                   // Last time program was used
	int session_timeout_seconds;
} session_t;

bool is_session_valid(void);
bool save_session(const char *email, const char *token);
bool load_session(session_t *session);
bool refresh_session(void);
bool clear_session(void);
char *get_current_user_email(void);

#endif // SESSION_H
