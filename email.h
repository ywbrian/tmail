#ifndef EMAIL_H
#define EMAIL_H

#include <stdbool.h>

bool login_to_gmail(const char *email, const char *password);
bool send_email(const char *to, const char *subject, const char *body);

#endif // EMAIL_H
