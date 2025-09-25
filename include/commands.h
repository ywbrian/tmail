#ifndef COMMANDS_H
#define COMMANDS_H

#include <stdbool.h>

/* Typedefs */
// command function pointer type declaration
typedef bool (*cmd_func_t)(int, char **);

// Command structure
typedef struct {
	const char *name;
	cmd_func_t func;
} command_t;

/* Function declarations */
int parse_global_flags(int argc, char **argv);
bool execute_cmd(int argc, char **argv);
bool cmd_login(int argc, char **argv);
bool validate_email(const char *email);

/* Command table declaration */
extern const command_t commands[];
extern const int num_commands;

#endif // COMMANDS_H
