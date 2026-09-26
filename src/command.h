#pragma once

#include <stddef.h>

#define ERR_CMDLINE_OK (0)
#define ERR_CMDLINE_NO_BUFFER (1 << 0)
#define ERR_CMDLINE_STRQUOT (1 << 1)

typedef struct command_s Command;

typedef struct
{
  size_t argc;
  char **argv;
} Arguments;

/// @brief Constructs a new command object
/// @param commandline The heap-allocated commandline buffer to own
/// @return A pointer to a Command, else NULL if no commandline is provided or if malloc(3) fails to allocate
Command *command_new(char *commandline);

/// @brief Frees all resources the Command owns. Note that this function frees the internal buffer passed on from `command_new`
/// @param cmd Pointer to command object
void command_free(Command *cmd);

/// @brief Returns the commandline passed from `command_new`
/// @param cmd Commandline object
/// @return Read-only pointer to the raw commandline buffer
const char *command_cmdline(const Command *const cmd);

/// @brief Puts the command line information (`argc` and `argv`) to `Args`
/// @param cmd Commandline object to read from
/// @param args Arguments object to put information into. `NULL` will be set when `command_tokenize` hasn't processed the `cmd`
void command_args(const Command *const cmd, Arguments *args);

/// @brief Returns the binary to execute
/// @param cmd Commandline object to read from
/// @return Read-only reference to the executable in `cmd`
const char *command_cmd(const Command *const cmd);

/// @brief A debug function meant to show data about the passed Command
/// @param cmd Command Object
void command_debug(const Command *const cmd);

/// @brief Tokenizes the internal buffer of `cmd` for command execution. Call this function before calling `command_args`
/// @param cmd Commandline object to read from
/// @return `ERR_CMDLINE_OK`
int command_tokenize(Command *const cmd);
