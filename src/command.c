#include "command.h"

#include "buffer.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

struct command_s
{
  char *buffer;
  char *cmd;
  Vec *argv;
};

Command *command_new(char *commandline)
{
  if (!commandline)
  {
    return NULL;
  }

  Command *cmd = malloc(sizeof(Command));
  if (!cmd)
  {
    return NULL;
  }
  Vec *argv = vec_new(sizeof(char *));
  if (!argv)
  {
    command_free(cmd);
    return NULL;
  }

  *cmd = (Command){
      .buffer = commandline,
      .cmd = NULL,
      .argv = argv,
  };

  return cmd;
}

void command_debug(Command *cmd)
{
  printf("===== COMMANDLINE DATA =====\n");
  if (cmd->buffer)
    printf("Buffer: %s\n", cmd->buffer);
  if (cmd->cmd)
    printf("Command: %s\n", cmd->cmd);
  if (vec_len(cmd->argv))
  {
    char **args = vec_data(cmd->argv);
    printf("Arguments:\n");
    for (int i = 0; i < vec_len(cmd->argv); i++)
    {
      printf("\t%d: %s\n", i, args[i]);
    }
  }
  printf("===== COMMANDLINE DATA =====\n");
}

void command_free(Command *cmd)
{
  free(cmd->buffer);
  free(cmd);
  cmd = NULL;
}

char *command_cmdline(Command *cmd)
{
  return cmd->buffer;
}

char *command_cmd(Command *cmd)
{
  return cmd->cmd;
}

void command_args(Command *cmd, Arguments *args)
{
  if (!args)
  {
    return;
  }

  *args = (Arguments){
      .argv = vec_data(cmd->argv),
      .argc = vec_len(cmd->argv)};
}

int command_tokenize(Command *cmd)
{
  if (!cmd || !cmd->buffer)
  {
    return ERR_CMDLINE_NO_BUFFER;
  }

  cmd->cmd = strtok(cmd->buffer, " ");

  char *current_token = NULL;
  do
  {
    current_token = strtok(NULL, " ");
    vec_add(cmd->argv, current_token);
  } while (current_token != NULL);

  return ERR_CMDLINE_OK;
}