#include <stdio.h>
#include <stdlib.h>

#include "line.h"
#include "command.h"
#include "builtins.h"
#include "search.h"

#include "builtins_impl.h"

Command *process_stdin(void)
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
    return NULL;
  }

  return cmd;
}

int process_command(Command *cmd, CallbackManager *cbm, Path *path, ShellContext *ctx)
{
  Arguments args;
  command_args(cmd, &args);

  char *program = find_program(command_cmd(cmd), path);
  if (program)
  {
    printf("Executable found at %s", program);

    free(program);
    return 0;
  }
  else
  {
    int retcode = callback_run(cbm, command_cmd(cmd), args.argv, args.argc, ctx);
    printf("$? = %d\n", retcode);

    // printf("No such executable found: %s", command_cmd(cmd));

    return retcode;
  }
}

int main(void)
{
  Path *path = malloc(sizeof(Path));
  if (!path)
  {
    perror("load_path");
    return -100;
  }

  load_path_variable(path);
  printf("Hello world!\n");

  CallbackManager *cbm = callback_manager_new();
  ShellContext ctx = (ShellContext){
      .cbm = cbm,
      .current_working_dir = NULL};

  register_builtins(cbm);

  Command *cmd = process_stdin();
  if (cmd)
  {
    command_debug(cmd);
    process_command(cmd, cbm, path, &ctx);
  }

  command_free(cmd);
  callback_manager_free(cbm);

  free(path->pathbuf);
  free(path);
  return 0;
}