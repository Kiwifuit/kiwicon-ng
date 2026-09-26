#include "search.h"

#ifdef _WIN32
#define PATHSEP ";"
#define LEN(arr) (sizeof(arr) / (sizeof((arr)[0])))

const char *EXECUTABLE_EXTENSIONS[] = {".exe", ".bat", ".cmd", ".com", ".ps1"};
#else
#define PATHSEP ":"

#endif

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "path.h"

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
  if (!path)
  {
    return;
  }

  char *path_var = getenv("PATH");
  if (!path_var)
  {
    return;
  }
  size_t path_len = strlen(path_var);
  char *path_str = calloc(path_len + 1, sizeof(char));

  memcpy(path_str, path_var, path_len + 1);

  split_path(path_str);
  path->pathbuf = path_str;
  path->pathlen = path_len;
}

#ifdef _WIN32
char *is_valid_program(char *dir, const char *prog, struct stat *stat_data)
{
  if (!dir || !prog || !(*dir) || !(*prog))
  {
    return NULL;
  }

  char *prog_path;
  for (size_t i = 0; i < LEN(EXECUTABLE_EXTENSIONS); i++)
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
#else
int is_file_executable(struct stat *stat_data)
{
  if (!stat_data || !S_ISREG(stat_data->st_mode))
  {
    return 0;
  }

  uid_t euid = geteuid();
  gid_t egid = getegid();

  if (stat_data->st_uid == euid)
  {
    return (stat_data->st_mode & S_IXUSR) ? 1 : 0;
  }

  if (stat_data->st_gid == egid)
  {
    return (stat_data->st_mode & S_IXGRP) ? 1 : 0;
  }

  return (stat_data->st_mode & S_IXOTH) ? 1 : 0;
}

char *is_valid_program(char *dir, const char *prog, struct stat *stat_data)
{
  if (!dir || !prog || !(*dir) || !(*prog))
  {
    return NULL;
  }

  char *prog_path = concat_path(dir, prog, NULL);

  if (stat(prog_path, stat_data))
  {
    free(prog_path);
    return NULL;
  }
  else if (is_file_executable(stat_data))
  {
    return prog_path;
  }

  free(prog_path);
  return NULL;
}
#endif

char *find_program(const char *progname, Path *path)
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
      return valid_prog;
    }
    current_path += current_path_len + 1;
    traversed += current_path_len + 1;
  }

  return NULL;
}