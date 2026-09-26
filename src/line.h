#pragma once

#ifndef KIWICON_LINE_WIDTH
#define KIWICON_LINE_WIDTH 256
#endif

/// @brief Fetches characters from stdin
/// @param prompt The prompt to display
/// @return A string with a length of at most `KIWICON_LINE_WIDTH` characters or `NULL` if failure
char *get_command(char *prompt);

/// @brief Strips the newline from the string
/// @param input Input string
void strip_newline(char *input);
