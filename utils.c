#include "utils.h"
#include "commands.h"
#include "version.h"

#include <ctype.h>
#include <stdio.h>

bool parse_args(int argc, const char **argv) {
	if (argc < 2 || !isalpha(argv[1][0])) {
		fprintf(stderr, "Usage: tmail <command> [options]\n");
		return false;
	}

	const char *cmd = argv[1];

	execute_cmd(cmd, argc - 2, (const char **)(argv + 2));

	return false;
}

void print_help(void) {
	printf("login   Login to an email account\n");
}

void print_version(void) {
	printf("tmail version %s\n", xstr(VERSION));
}
