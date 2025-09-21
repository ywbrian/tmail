#ifndef COMMANDS_H
#define COMMANDS_H

#include <stdbool.h>

/* Typedefs */
// command function pointer type declaration
typedef bool (*cmd_func_t)(int, const char **);

// Command structure
typedef struct {
	const char *name;
	cmd_func_t func;
} command_t;

/* Function declarations */
int parse_global_flags(int argc, const char **argv);
bool execute_cmd(const char *cmd_name, int argc, const char **argv);
bool cmd_login(int argc, const char **argv);
bool validate_email(const char *email);

/* Command table declaration */
extern const command_t commands[];
extern const int n_commands;

#endif // COMMANDS_H
