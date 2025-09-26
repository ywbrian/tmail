#ifndef TMAIL_COMMANDS_H
#define TMAIL_COMMANDS_H

#include <stdbool.h>

/* Custom types */
typedef int (*command_func_t)(int, char **); // Command function pointer

// Command structure
typedef struct {
	const char *name;
	command_func_t func;
} command_t;

/* Function declarations */
int dispatch_command(int argc, char **argv);
int command_login(int argc, char **argv);

/* Command table declaration */
extern const command_t commands[];
extern const int num_commands;

#endif // TMAIL_COMMANDS_H
