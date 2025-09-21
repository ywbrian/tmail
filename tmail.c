#include "commands.h"
#include "utils.h"

int main(int argc, char **argv) {
	if (parse_global_flags(argc, (const char **)argv) == 0) {
		return 0;
	}

	if (!parse_args(argc, (const char **)(argv))) {
		return 0;
	}

	return 0;
}
