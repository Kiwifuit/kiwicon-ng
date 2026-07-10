#pragma once

#include <stddef.h>

#define ERR_CMDLINE_OK 0
#define ERR_CMDLINE_NO_BUFFER 1

typedef struct command_s Command;

typedef struct
{
  size_t argc;
  char **argv;
} Arguments;

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

/*
Returns argument data about cmd and
puts it into args
*/
void cmd_args(Command *cmd, Arguments *args);

/*
Returns the command to execute
*/
char *cmd_command(Command *cmd);

void debug_command(Command *cmd);

int parse_token(Command *cmd);
