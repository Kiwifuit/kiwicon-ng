#include "builtins_impl.h"

#include "builtins.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

Callback *find_prog_help(char *prog, Callback **cbs, size_t cb_count)
{
  for (size_t i = 0; i < cb_count; i++)
  {
    if (!strcmp(prog, callback_name(cbs[i])))
      return cbs[i];
  }
}

int builtin_echo(char **argv, size_t argc, ShellContext *ctx)
{
  if (argc < 1)
    return 1;

  printf("Echo: %s\n", argv[0]);
  return 0;
}

int builtin_exit(char **argv, size_t argc, ShellContext *ctx)
{
  exit(0);
  return 0;
}

int builtin_help(char **argv, size_t argc, ShellContext *ctx)
{
  if (argc == 1)
  {
    char *prog = argv[0];
  }
}

void register_builtins(CallbackManager *cbm)
{
  callback_add(cbm, "echo", "Prints to the screen", builtin_echo);
  callback_add(cbm, "exit", "Exits the shell", builtin_exit);
}