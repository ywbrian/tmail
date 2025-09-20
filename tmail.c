#include "commands.h"

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <regex.h>
#include <unistd.h>
#include <stdlib.h>

/* Function Prototypes */
bool handle_args(int argc, char** argv);

/* Miscellaneous */
void print_help_message(void);

int main(int argc, char** argv) {
    if (!handle_args(argc, argv)) { return 0; }

    return 0;
}

bool handle_args(int argc, char** argv) {
    if (argc < 2 || !isalpha(argv[1][0])) {
        fprintf(stderr, "Usage: tmail <command> [options]\n");
        return false;
    }

    char* cmd = argv[1];

    execute_cmd(cmd, argc - 2, (const char**)(argv + 2));

    return false;
}


