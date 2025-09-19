#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <regex.h>
#include <unistd.h>
#include <stdlib.h>

typedef bool (*cmd_func)(int, char**);

typedef struct {
    const char *name;
    cmd_func func;
} command_t;

/* Function Prototypes */
bool handle_args(int argc, char** argv);

/* Commands */
bool cmd_login(int argc, char** argv);
bool validate_email(const char* email);

command_t commands[] = {
    {"login", cmd_login},
    {NULL, NULL}
};

/* Miscellaneous */
void print_help_message(void);

int main(int argc, char** argv) {
    handle_args(argc, argv);

    return 0;
}

bool handle_args(int argc, char** argv) {
    if (argc < 2 || !isalpha(argv[1][0])) {
        fprintf(stderr, "Usage: tmail <command> [options]\n");
        return false;
    }

    char* cmd = argv[1];

    for (int i = 0; commands[i].name; i++) {
        if (strcmp(argv[1], commands[i].name) == 0) {
            commands[i].func(argc - 2, argv + 2);
            return true;
        }
    }

    fprintf(stderr, "Unknown command: %s\n", cmd);
    return false;
}

bool cmd_login(int argc, char** argv) {
    if (argc != 1) {
        fprintf(stderr, "Usage: tmail login <address>\n");
        return false;
    }

    const char* email = argv[0];

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

bool validate_email(const char* email) {
    if (!email || email[0] == '\0') {
        fprintf(stderr, "Error: email address is empty\n");
        return false; 
    }

    if (strlen(email) > 254) {
        fprintf(stderr, "Error: email address exceeds maximum length (254)\n");
        return false;
    }

    regex_t regex;
    int reti;

    const char* pattern = "^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\\.[A-Za-z]{2,}$";

    reti = regcomp(&regex, pattern, REG_EXTENDED | REG_NOSUB);
    if (reti) {
        fprintf(stderr, "Error: failed to compile regex\n");
        return false;
    }

    reti = regexec(&regex, email, 0, NULL, 0);
    regfree(&regex);

    if (reti != 0) {
        fprintf(stderr, "Error: invalid email address format\n");
        return false;
    }

    return true;
}

void print_help_message(void) {
    printf("--- List of commands used in TMail ---");
    printf("login <email>   Login to an email account");
}

