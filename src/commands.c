#include "commands.h"
#include "utils.h"
#include "version.h"
#include "constants.h"

#include <ctype.h>
#include <regex.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int dispatch_command(int argc, char **argv) {
    const char *cmd_name = argv[0];
	for (int i = 0; i < num_commands; i++) {
		if (strcmp(cmd_name, commands[i].name) == 0) {
			return commands[i].func(argc, argv);
		}
	}
	fprintf(stderr, "Unknown command: %s\n", cmd_name);
	return 1;
}

int cmd_login(int argc, char **argv) {
    UNUSED(argv);

    if (argc > 1) { 
        print_with_prefix(stderr, "too many arguments\n");
        return 1;
    }

	char email[MAX_EMAIL_ADDRESS_LENGTH]; // +1 for null terminator
	printf("Enter email address: ");
	if (fgets(email, sizeof(email), stdin) == NULL) {
		fprintf(stderr, "Invalid email address");
        return 1;
	}

	// Remove trailing newline if present
	email[strcspn(email, "\n")] = '\0';

	if (!validate_email(email)) {
		return 1;
	}

	return 0;
}

/* Command table */
const command_t commands[] = {{"login", cmd_login}};

const int num_commands = sizeof(commands) / sizeof(command_t);

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
		fprintf(stderr, "email address exceeds maximum length (%d)\n",
		        MAX_EMAIL_ADDRESS_LENGTH);
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
