#include "line.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *get_command(char *prompt)
{
  char *buffer = calloc(KIWICON_LINE_WIDTH, sizeof(char));
  if (!buffer)
  {
    return NULL;
  }

  printf("%s> ", prompt);
  if (!fgets(buffer, KIWICON_LINE_WIDTH, stdin))
  {
    return NULL;
  }
  return buffer;
}

void strip_newline(char *input)
{
  input[strlen(input) - 1] = 0;
}