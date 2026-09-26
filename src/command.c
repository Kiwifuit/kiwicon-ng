#include "command.h"

#include "buffer.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

enum command_state_e
{
  STATE_NONE,
  STATE_QUOTING,
};

struct command_flags_s
{
  enum command_state_e current_state;
  char *token_start;
};
struct command_s
{
  char *buffer;
  char *cmd;
  Vec *argv;

  struct command_flags_s state;
};

Command *
command_new(char *commandline)
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
      .state = {
          .current_state = STATE_NONE,
          .token_start = NULL,
      },
  };

  return cmd;
}

void command_debug(const Command *const cmd)
{
  if (!cmd)
    return;

  printf("===== COMMANDLINE DATA =====\n");
  if (cmd->buffer)
    printf("Buffer: %s\n", cmd->buffer);
  if (cmd->cmd)
    printf("Command: %s\n", cmd->cmd);
  if (vec_len(cmd->argv))
  {
    char **args = vec_data(cmd->argv);
    printf("Arguments:\n");
    for (size_t i = 0; i < vec_len(cmd->argv); i++)
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

const char *command_cmdline(const Command *const cmd)
{
  return cmd->buffer;
}

const char *command_cmd(const Command *const cmd)
{
  return cmd->cmd;
}

void command_args(const Command *const cmd, Arguments *args)
{
  if (!args)
  {
    return;
  }

  *args = (Arguments){
      .argv = vec_data(cmd->argv),
      .argc = vec_len(cmd->argv)};
}

int command_tokenize(Command *const cmd)
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
    if (!current_token)
    {
      break;
    }

    size_t ct_len = strlen(current_token);

    if (current_token[0] == '"' && cmd->state.current_state == STATE_NONE)
    {
      cmd->state.current_state = STATE_QUOTING;
      cmd->state.token_start = current_token;
      current_token[ct_len] = ' ';
    }
    else if (current_token[ct_len - 1] == '"' && (cmd->state.current_state == STATE_QUOTING))
    {
      cmd->state.current_state = STATE_NONE;
    }
    else if (cmd->state.current_state == STATE_QUOTING)
    {
      current_token[ct_len] = ' ';
    }

    if (cmd->state.current_state != STATE_QUOTING)
    {
      if (cmd->state.token_start)
        vec_add(cmd->argv, cmd->state.token_start);
      else
        vec_add(cmd->argv, current_token);

      cmd->state.token_start = NULL;
    }
  } while (current_token != NULL);

  if (cmd->state.current_state == STATE_QUOTING)
  {
    return ERR_CMDLINE_STRQUOT;
  }

  return ERR_CMDLINE_OK;
}