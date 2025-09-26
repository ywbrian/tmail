#include "commands.h"
#include "utils.h"
#include "constants.h"
#include "auth.h"

#include <ctype.h>
#include <regex.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int dispatch_command(int argc, char **argv) {
    const char *command_name = argv[0];
	for (int i = 0; i < num_commands; i++) {
		if (strcmp(command_name, commands[i].name) == 0) {
			return commands[i].func(argc, argv);
		}
	}
	fprintf(stderr, "Unknown command: %s\n", command_name);
	return 1;
}

int command_login(int argc, char **argv) {
    UNUSED(argv);

    if (argc > 1) { 
        print_with_prefix(stderr, "too many arguments\n");
        return 1;
    }

    esp_t esp;
    if ((esp = prompt_for_esp()) == ESP_INVALID) {
        return 1;
    }

	char email[MAX_EMAIL_ADDRESS_LENGTH];
	printf("Enter email address: ");
	if (fgets(email, sizeof(email), stdin) == NULL) {
		fprintf(stderr, "Invalid email address\n");
        return 1;
	}
	email[strcspn(email, "\n")] = '\0'; // Remove any trailing newline

	if (!validate_email(email)) {
		return 1;
	}

    return authenticate_email(esp, email);
}

/* Command table */
const command_t commands[] = {{"login", command_login}};

const int num_commands = sizeof(commands) / sizeof(command_t);
