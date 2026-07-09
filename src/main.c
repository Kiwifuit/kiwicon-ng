#include <stdio.h>
#include <stdlib.h>

#include "line.h"

int main()
{
  printf("Hello world!\n");
  char *cmd = get_command("Input command");
  strip_newline(cmd);

  printf("Command input: %s\n", cmd);
  free(cmd);
  return 0;
}