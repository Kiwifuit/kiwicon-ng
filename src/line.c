#include "line.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *get_command(const char *prompt)
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
  size_t newline_loc = strlen(input) - 1;
  if (input[newline_loc] == '\n')
    input[newline_loc] = 0;
}