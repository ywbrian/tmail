#ifndef SESSION_H
#define SESSION_H

#include <stdbool.h>
#include <time>

#define CONFIG_FILE ".tmail_config"
#define MAX_EMAIL_ADDRESS_LENGTH 254
#define MAX_SHA256_HASH_LENGTH 65

typedef struct {
	char email[MAX_EMAIL_ADDRESS_LENGTH + 1];
	char password_hash[MAX_SHA256_HASH_LENGTH];
	time_t last_login;
	int session_timeout_hours;
} session_t;

bool is_session_valid(void);
bool save_session(const char *email, const char *password);
bool load_session(session_t *session);
bool clear_session(void);
char *get_current_user_email(void);

#endif // SESSION_H
