#pragma once

#ifndef KIWICON_LINE_WIDTH
#define KIWICON_LINE_WIDTH 256
#endif

/*
Fetches characters from stdin, using
`prompt` as the prompt.

Returns a string with at most a length
of `KIWICON_LINE_WIDTH` on success, and
`NULL` otherwise.
*/
char *get_command(char *prompt);

/*
Strips the newline of the input
*/
void strip_newline(char *input);
