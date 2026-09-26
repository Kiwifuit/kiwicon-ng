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

/*
Creates a callback manager
*/
CallbackManager *callback_manager_new();

/*
Frees the resources associated with the callback
manager `cbm`
*/
void callback_manager_free(CallbackManager *cbm);

/*
Adds a callback to the callback manager and
associates it to `name`
*/
int callback_add(CallbackManager *cbm, char *restrict name, const char *restrict help_doc, BuiltinEntrypoint entrypoint);

/*
Finds the callback associated to `name`
and executes it with the contents of
`argc` and `argv`
*/
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
