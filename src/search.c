#include "search.h"

#ifdef _WIN32
#define PATHSEP ";"
#define LEN(arr) (sizeof(arr) / (sizeof((arr)[0])))

const char *EXECUTABLE_EXTENSIONS[] = {".exe", ".bat", ".cmd", ".com", ".ps1"};
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
// #include <errno.h>

void split_path(char *path)
{
  char *current_path = strtok(path, PATHSEP);

  while (current_path)
  {
    current_path = strtok(NULL, PATHSEP);
  }
}

void load_path_variable(Path *path)
{
  char *path_var = getenv("PATH");
  if (!path_var)
  {
    return;
  }
  size_t path_len = strlen(path_var);
  char *path_str = calloc(path_len + 1, sizeof(char));

  if (!path)
  {
    return;
  }
  errno_t retcode = strcpy_s(path_str, path_len + 1, path_var);
  if (retcode)
  {
    perror("load_path");
    free(path);
    return;
  }

  split_path(path_str);
  path->pathbuf = path_str;
  path->pathlen = path_len;
}

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

  size_t total_size = dir_len + prog_len + ext_len + 1;
  if (dir[dir_len - 1] != '\\')
  {
    total_size++;
  }

  char *prog_path = calloc(total_size, sizeof(char));

  if (!prog_path)
  {
    return NULL;
  }

  if (dir[dir_len - 1] != '\\')
  {
    snprintf(prog_path, total_size, "%s\\%s", dir, prog);
  }
  else
  {
    snprintf(prog_path, total_size, "%s%s", dir, prog);
  }

  if (ext)
  {
    snprintf(prog_path, total_size, "%s%s", prog_path, ext);
  }

  return prog_path;
}

char *is_valid_program(char *dir, char *prog, struct stat *stat_data)
// char *is_valid_program(char *dir, char *prog)
{
  if (!dir || !prog || !(*dir) || !(*prog))
  {
    return NULL;
  }

  char *prog_path;
  for (int i = 0; i < LEN(EXECUTABLE_EXTENSIONS); i++)
  {
    prog_path = concat_path(dir, prog, EXECUTABLE_EXTENSIONS[i]);
    if (is_executable(prog_path, stat_data))
    {
      return prog_path;
    }
    free(prog_path);
  }

  return NULL;
}

char *find_program(char *progname, Path *path)
{
  char *current_path = path->pathbuf;
  size_t traversed = 0;
  struct stat stat_data;

  while (traversed < path->pathlen)
  {
    size_t current_path_len = strlen(current_path);
    char *valid_prog = is_valid_program(current_path, progname, &stat_data);

    if (valid_prog)
    {
      printf("Program found: %s\n", valid_prog);
      return valid_prog;
    }

    current_path += current_path_len + 1;
    traversed += current_path_len + 1;
  }

  return NULL;
}