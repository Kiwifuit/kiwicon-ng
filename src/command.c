#include "command.h"

#include <stdlib.h>
#include <string.h>
#include <stdint.h>

struct command_s
{
  char *buffer;
  char *cmd;
  char **argv;
  uint16_t argc;
};

Command *new_command(char *commandline)
{
  Command *cmd = malloc(sizeof(Command));
  if (!cmd)
  {
    return NULL;
  }

  cmd->buffer = commandline;
  return cmd;
}

void free_command(Command *cmd)
{
  free(cmd->buffer);
  free(cmd);
  cmd = NULL;
}

char *commandline(Command *cmd)
{
  return cmd->buffer;
}