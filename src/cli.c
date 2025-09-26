#include "cli.h"
#include "version.h"
#include "utils.h"
#include "commands.h"

#include <stdio.h>
#include <string.h>

/**
 * Parse and handle any global flags in command line arguments
 *
 * Parameters:
 *  argc - the argument count
 *  argv - the argument strings
 *
 * Return:
 *  0 if program should exit with success after parsing flag
 *  1 if program should exit with failure after parsing flag
 *  -1 if no global flags provided or program should continue
 */
int handle_global_flags(int argc, char **argv) {
	if (argc == 2) {
		if (strcmp(argv[1], "--help") == 0) {
			show_help();
            return 0;
		} else if (strcmp(argv[1], "--version") == 0) {
			show_version();
            return 0;
		}
	}

	return -1;
}

int dispatch_args(int argc, char **argv) {
	if (argc < 2) { // No subcommand given
		fprintf(stderr, "Usage: tmail <command> [options]\n");
		return 1;
	}

	return dispatch_command(argc - 1, argv + 1);
}

/**
 * Print a help message to stdout, containing a list of commands and
 * their purposes.
 *
 * Parameters:
 *  none
 *
 * Return:
 *  void
 */
void show_help(void) {
    printf("Usage:\n");
    printf("    tmail <command> [options]\n\n");
    printf("Commands:\n");
	printf("    login   Login to an email account\n");
	printf("    send    Send an email\n");
	printf("    inbox   View inbox\n");
	printf("    logout  Logout of current session\n");
    printf("\n");
    printf("Global options:\n");
	printf("    --help      Show this help message\n");
	printf("    --version   Show program version\n");
}

/**
 * Print the current application version to stdout
 *
 * Parameters:
 *  None
 *
 * Return:
 *  None
 */
void show_version(void) {
	printf("tmail version %s\n", xstr(TMAIL_VERSION));
}
