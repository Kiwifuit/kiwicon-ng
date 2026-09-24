#include "builtins_impl.h"

#include "builtins.h"
#include <stdlib.h>
#include <stdio.h>

int builtin_echo(char **argv, size_t argc)
{
  if (argc < 1)
    return 1;

  printf("Echo: %s\n", argv[0]);
  return 0;
}

int builtin_exit(char **argv, size_t argc)
{
  exit(0);
  return 0;
}

void register_builtins(CallbackManager *cbm)
{
  callback_add(cbm, "echo", "Prints to the screen", builtin_echo);
  callback_add(cbm, "exit", "Exits the shell", builtin_exit);
}