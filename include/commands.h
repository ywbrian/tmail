#ifndef COMMANDS_H
#define COMMANDS_H

#include <stdbool.h>

/* Custom types */
typedef int (*cmd_func_t)(int, char **); // Command function pointer

// Command structure
typedef struct {
	const char *name;
	cmd_func_t func;
} command_t;

/* Function declarations */
int dispatch_command(int argc, char **argv);
int cmd_login(int argc, char **argv);
bool validate_email(const char *email);

/* Command table declaration */
extern const command_t commands[];
extern const int num_commands;

#endif // COMMANDS_H
