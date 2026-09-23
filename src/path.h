#pragma once

#include <sys/stat.h>

/// @brief Checks if a path is executable
/// @param path Path of the program to check
/// @param stat_data Scratch for `stat(2)`
/// @return 1 if `path` is executable, and 0 otherwise
int is_executable(char *path, struct stat *stat_data);

/// @brief Concatenates the path into one heap-allocated string
/// @param dir Base directory
/// @param prog Program name
/// @param ext Optional file extension
/// @return Heap-allocated string to fully concatenated path
char *concat_path(char *dir, char *prog, const char *ext);
