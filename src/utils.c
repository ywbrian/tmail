#include "utils.h"
#include "constants.h"

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <regex.h>


/**
 * Helper function to verify syntax of a given email address
 *
 * Parameters:
 *  email - the string email address to validate
 *
 * Return: true if the email is valid, false otherwise
 */
bool validate_email(const char *email) {
	if (!email || email[0] == '\0') {
		fprintf(stderr, "email address cannot be empty\n");
		return false;
	}

	if (strlen(email) > MAX_EMAIL_ADDRESS_LENGTH) {
		fprintf(stderr, "email address exceeds maximum length (%lu>%d)\n",
		        strlen(email), MAX_EMAIL_ADDRESS_LENGTH);
		return false;
	}

	regex_t regex;
	int reti;

	const char *pattern =
	        "^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\\.[A-Za-z]{2,}$";

	reti = regcomp(&regex, pattern, REG_EXTENDED | REG_NOSUB);
	if (reti) {
		fprintf(stderr, "fatal: failed to compile regex\n");
		return false;
	}

	reti = regexec(&regex, email, 0, NULL, 0);
	regfree(&regex);

	if (reti != 0) {
		fprintf(stderr, "invalid email address format\n");
		return false;
	}

	return true;
}

/**
 * Print a given string to a stream with the "tmail: " prefix
 *
 * Parameters:
 *  stream - The output stream
 *  fmt    - The string format specifiers
 *  ...    - The arguments corresponding to the format specifiers
 *
 * Return:
 *  None
 */
void print_with_prefix(FILE *stream, const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);

    fputs("tmail: ", stream);
    vfprintf(stream, fmt, args);
    fflush(stream);

    va_end(args);
}
