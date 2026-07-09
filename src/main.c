#include <stdio.h>
#include <stdlib.h>

#include "line.h"
#include "command.h"

Command *process_stdin()
{
  char *cmdline = get_command("Input command");
  if (!cmdline)
  {
    perror("get_command");
    return NULL;
  }
  strip_newline(cmdline);

  Command *cmd = new_command(cmdline);
  if (!cmd)
  {
    perror("new_command");
    free(cmdline);
    return NULL;
  }

  int retcode = parse_token(cmd);
  if (retcode != ERR_CMDLINE_OK)
  {
    printf("parse_token: error %x", retcode);
    free_command(cmd);
  }

  return cmd;
}

int main()
{
  printf("Hello world!\n");
  Command *cmd = process_stdin();
  printf("Command: %s\n", commandline(cmd));
  debug_command(cmd);

  free_command(cmd);
  return 0;
}