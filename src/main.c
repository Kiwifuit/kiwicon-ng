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

  Command *cmd = command_new(cmdline);
  if (!cmd)
  {
    perror("command_new");
    free(cmdline);
    return NULL;
  }

  int retcode = command_tokenize(cmd);
  if (retcode != ERR_CMDLINE_OK)
  {
    printf("command_tokenize: error %x", retcode);
    command_free(cmd);
  }

  return cmd;
}

int process_command(Command *cmd, CallbackManager *cbm)
{
  Arguments args;
  command_args(cmd, &args);

  int retcode = callback_run(cbm, command_cmd(cmd), args.argv, args.argc);
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
  command_debug(cmd);
  process_command(cmd, cbm);

  command_free(cmd);
  callback_manager_free(cbm);
  return 0;
}