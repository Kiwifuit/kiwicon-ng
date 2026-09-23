#pragma once

#include <stddef.h>

typedef struct
{
  char *pathbuf;
  size_t pathlen;
} Path;

/// @brief Loads $PATH
/// @param path Output of the function
void load_path_variable(Path *path);

/// @brief Finds a program and resolves the executable
/// @param progname Name of the program
/// @param path Buffer containing data from `load_path_variable`
/// @return Absolute path to executable, or NULL if not found
char *find_program(char *progname, Path *path);