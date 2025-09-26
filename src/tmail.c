#include "cli.h"

int main(int argc, char **argv) {
    int flag_result = handle_global_flags(argc, argv);
    if (flag_result == 0) { return 0; }
    if (flag_result == 1) { return 1; }

    dispatch_args(argc, argv);

    return 0;
}
