#include <stdio.h>
#include <stdlib.h>

#include "line.h"
#include "command.h"
#include "builtins.h"

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

int process_command(Command *cmd, CallbackManager *cbm)
{
  Arguments args;
  cmd_args(cmd, &args);

  int retcode = callback_run(cbm, cmd_command(cmd), args.argv, args.argc);
  printf("$? = %d\n", retcode);
}

int builtin_echo(char **argc, size_t argv)
{
  if (argv < 1)
    return 1;

  printf("Echo: %s\n", argc[0]);
  return 0;
}

int main()
{
  printf("Hello world!\n");

  CallbackManager *cbm = callback_manager_new();

  if (callback_add(cbm, "echo", NULL, builtin_echo))
    perror("callback_add");

  Command *cmd = process_stdin();
  printf("Command: %s\n", commandline(cmd));
  debug_command(cmd);
  process_command(cmd, cbm);

  free_command(cmd);
  callback_manager_free(cbm);
  return 0;
}