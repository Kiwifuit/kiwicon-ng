#pragma once

#define ERR_BUILTIN_OK 0
#define ERR_BUILTIN_NULLPTR 1
#define ERR_BUILTIN_ERRNO 2
#define ERR_BUILTIN_NOTFOUND 3
#define ERR_BUILTIN_ERR 4

#include <stddef.h>

typedef struct callback_mgr_s CallbackManager;
typedef struct callback_s Callback;

typedef struct
{
  CallbackManager *cbm;
  char *current_working_dir;
} ShellContext;

typedef int (*BuiltinEntrypoint)(char **, size_t, ShellContext *);

/// @brief Creates a callback manager. Must be freed with `callback_manager_free`
/// @return Heap allocated callback manager
CallbackManager *callback_manager_new();

/// @brief Frees the callback manager
/// @param cbm Pointer to the callback manager
void callback_manager_free(CallbackManager *cbm);

/// @brief Adds a particular function as a "shell builtin"
/// @param cbm Callback manager
/// @param name Friendly name of the function. Shell users enter this
/// @param help_doc Short help string about the builtin
/// @param entrypoint Function to call
/// @return `ERR_BUILTIN_OK` if the callback was added successfully
int callback_add(CallbackManager *cbm, char *restrict name, const char *restrict help_doc, BuiltinEntrypoint entrypoint);

/// @brief Searches for a callback in the manager and runs it with the given arguments
/// @param cbm Callback manager
/// @param name The friendly name of the builtin
/// @param argv Arguments to pass
/// @param argc Number of arguments passed
/// @return `ERR_BUILTIN_OK` if the callback was called successfully
int callback_run(CallbackManager *cbm, char *name, char *argv[], size_t argc, ShellContext *state);

/// @brief Fetches all the callbacks in the manager
/// @param cbm Pointer to callback manager
/// @param cbn Number of callbacks registered
/// @return A list of all callbacks
Callback **callback_get_all(CallbackManager *cbm, size_t *cbn);

/// @brief Fetches the name of the callback
/// @param cb Callback pointer
/// @return Pointer to callback friendly name
char *callback_name(Callback *cb);

/// @brief Fetches the help doc of the callback
/// @param cb Callback pointer
/// @return Pointer to help doc
char *callback_help(Callback *cb);
