#pragma once

#define ERR_BUILTIN_OK 0
#define ERR_BUILTIN_NULLPTR 1
#define ERR_BUILTIN_ERRNO 2
#define ERR_BUILTIN_NOTFOUND 3
#define ERR_BUILTIN_ERR 4

#include <stddef.h>

typedef int (*BuiltinEntrypoint)(char **, size_t);
typedef struct callback_mgr_s CallbackManager;

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
int callback_run(CallbackManager *cbm, char *name, char *argv[], size_t argc);
