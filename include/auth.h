#ifndef TMAIL_AUTH_H
#define TMAIL_AUTH_H

#include "constants.h"
#include "session.h"

int authenticate_email(esp_t esp, const char *email);
int test_imap_connection(const char *email, const char *password,
        session_t *session);

/* Gmail */
int authenticate_gmail(const char *email);
bool test_gmail_imap_connection(const char *email, const char *password,
        session_t *session);

int read_password(char *password, size_t size);

esp_t prompt_for_esp(void);

#endif // TMAIL_AUTH_H
