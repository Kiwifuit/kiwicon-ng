#pragma once

#define ERR_CMDLINE_OK 0
#define ERR_CMDLINE_NO_BUFFER 1

typedef struct command_s Command;

/*
Constructs a new command object, owning the
commandline buffer. Returns NULL when
`commandline` is NULL, or when malloc(3)
fails to allocate memory for the commandline
*/
Command *new_command(char *commandline);

/*
Frees the resources inside a command
*/
void free_command(Command *cmd);

/*
Returns the commandline passed inside of
`cmd`
*/
char *commandline(Command *cmd);

void debug_command(Command *cmd);

int parse_token(Command *cmd);
