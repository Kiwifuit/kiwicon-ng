#pragma once

#define ERR_BUILTIN_OK 0
#define ERR_BUILTIN_NULLPTR 1
#define ERR_BUILTIN_ERRNO 2
#define ERR_BUILTIN_NOTFOUND 3
#define ERR_BUILTIN_ERR 4

#include <stddef.h>

typedef int (*BuiltinEntrypoint)(char **, size_t);
typedef struct callback_mgr_s CallbackManager;

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
int callback_run(CallbackManager *cbm, char *name, char *argv[], size_t argc);
