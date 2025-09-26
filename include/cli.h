#ifndef TMAIL_CLI_H
#define TMAIL_CLI_H

/* Command-line argument parsing */
int handle_global_flags(int argc, char **argv);
int dispatch_args(int argc, char **argv);

/* Console messages */
void show_help(void);
void show_version(void);

#endif // TMAIL_CLI_H
