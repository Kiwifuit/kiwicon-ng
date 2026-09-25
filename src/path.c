#include "path.h"

#include <stdio.h>
#include <stdlib.h>

int is_executable(char *path, struct stat *stat_data)
{
  if (!stat(path, stat_data) && stat_data->st_size > 0)
  {
    return 1;
  }
  return 0;
}

char *concat_path(char *dir, char *prog, const char *ext)
{
  if (!dir || !prog || !(*dir) || !(*prog) || !ext || !(*ext))
  {
    return NULL;
  }

  size_t dir_len = strlen(dir);
  size_t prog_len = strlen(prog);
  size_t ext_len = 0;
  if (ext)
  {
    ext_len = strlen(ext);
  }

  size_t total_size = dir_len + prog_len + ext_len + 2;
  if (dir[dir_len - 1] != '\\')
  {
    total_size++;
  }

  char *prog_path = calloc(total_size, sizeof(char));
  char *pos = prog_path;

  if (!prog_path)
  {
    return NULL;
  }

  pos += snprintf(pos, total_size - (pos - prog_path), "%s", dir);
  if (dir[dir_len - 1] != '\\')
  {
    pos += snprintf(pos, total_size - (pos - prog_path), "\\");
  }
  pos += snprintf(pos, total_size - (pos - prog_path), "%s", prog);
  pos += snprintf(pos, total_size - (pos - prog_path), "%s", ext);

  return prog_path;
}
