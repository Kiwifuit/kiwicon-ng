#pragma once

typedef struct command_s Command;

/*
Constructs a new command object, owning the
commandline buffer.
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
