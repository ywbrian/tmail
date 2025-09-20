#include "commands.h"

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <regex.h>
#include <unistd.h>

#define MAX_EMAIL_ADDRESS_LENGTH 254

bool execute_cmd(const char *cmd_name, int argc, const char **argv) {
    for (int i = 0; i < n_commands; i++) {
        if (strcmp(cmd_name, commands[i].name) == 0) {
            return commands[i].func(argc - 2, (const char **)(argv + 2));
        }
    }
    fprintf(stderr, "Unknown command: %s\n", cmd_name);
    return false;
}

bool cmd_login(int argc, const char** argv) {
    char email[MAX_EMAIL_ADDRESS_LENGTH + 1]; // +1 for '\0'
    printf("Enter email address: ");
    if (fgets(email, sizeof(email), stdin) == NULL) {
        fprintf(stderr, "Invalid email address");
    }

    // Remove trailing newline if present
    email[strcspn(email, "\n")] = '\0';

    if (!validate_email(email)) {
        return false;
    }

    char *pw = getpass("Password: ");
    if (!pw) {
        fprintf(stderr, "Failed to read password");
        return false;
    }

    size_t plen = strlen(pw);
    if (plen) {
        memset(pw, 0, plen);
    }

    return true;
}

/* Command table */
const command_t commands[] = {
    {"login", cmd_login}
};

const int n_commands = sizeof(commands) / sizeof(command_t);

/*
 * Helper function to verify syntax of a given email address
 *
 * email: the string email address to validate
 *
 * Return: true if the email is valid, false otherwise
 *
 */
bool validate_email(const char* email) {
    if (!email || email[0] == '\0') {
        fprintf(stderr, "Email address cannot be empty\n");
        return false; 
    }

    if (strlen(email) > MAX_EMAIL_ADDRESS_LENGTH) {
        fprintf(stderr,
                "Email address exceeds maximum length (%d)\n",
                MAX_EMAIL_ADDRESS_LENGTH);
        return false;
    }

    regex_t regex;
    int reti;

    const char* pattern =
        "^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\\.[A-Za-z]{2,}$";

    reti = regcomp(&regex, pattern, REG_EXTENDED | REG_NOSUB);
    if (reti) {
        fprintf(stderr, "Error: failed to compile regex\n");
        return false;
    }

    reti = regexec(&regex, email, 0, NULL, 0);
    regfree(&regex);

    if (reti != 0) {
        fprintf(stderr, "Invalid email address format\n");
        return false;
    }

    return true;
}
