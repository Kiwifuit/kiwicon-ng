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
Command *command_new(char *commandline);

/*
Frees the resources inside a command
*/
void command_free(Command *cmd);

/*
Returns the commandline passed inside of
`cmd`
*/
char *command_cmdline(Command *cmd);

/*
Returns argument data about cmd and
puts it into args
*/
void command_args(Command *cmd, Arguments *args);

/*
Returns the command to execute
*/
char *command_cmd(Command *cmd);

/*
Displays debug information about
cmd to the terminal
*/
void command_debug(Command *cmd);

/*
Tokenizes the buffer inside of
`cmd`
*/
int command_tokenize(Command *cmd);
