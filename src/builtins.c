#include "builtins.h"

#include "buffer.h"

#include <string.h>
#include <stdlib.h>

struct callback_mgr_s
{
  Vec *callbacks;
};

struct callback_s
{
  const char *name;
  const char *help;
  BuiltinEntrypoint func;
};

CallbackManager *callback_manager_new(void)
{
  CallbackManager *cbm = malloc(sizeof(CallbackManager));
  if (!cbm)
  {
    return NULL;
  }

  cbm->callbacks = vec_new(sizeof(struct callback_s *));
  if (!cbm->callbacks)
  {
    cbm->callbacks = NULL;
    free(cbm);
  }

  return cbm;
}

void callback_manager_free(CallbackManager *cbm)
{
  struct callback_s **callbacks = vec_data(cbm->callbacks);
  if (!callbacks)
    return;

  for (size_t i = 0; i < vec_len(cbm->callbacks); i++)
  {
    struct callback_s *current_callback = callbacks[i];

    if (current_callback)
      free(current_callback);
  }

  vec_free(cbm->callbacks);
  free(cbm);
  cbm = NULL;
}

int callback_add(CallbackManager *cbm, char *restrict name, const char *restrict help_doc, BuiltinEntrypoint entrypoint)
{
  struct callback_s *callback = malloc(sizeof(struct callback_s));
  if (!callback)
  {
    return ERR_BUILTIN_ERRNO;
  }

  *callback = (struct callback_s){
      .name = name,
      .help = help_doc,
      .func = entrypoint};

  vec_add(cbm->callbacks, callback);
  return ERR_BUILTIN_OK;
}

int callback_run(CallbackManager *cbm, char *name, char *argv[], size_t argc, ShellContext *state)
{
  struct callback_s **callbacks = vec_data(cbm->callbacks);
  if (!callbacks)
    return ERR_BUILTIN_NULLPTR;

  struct callback_s *found_callback;

  for (size_t i = 0; i < vec_len(cbm->callbacks); i++)
  {
    struct callback_s *current_callback = callbacks[i];

    if (current_callback && !strcmp(current_callback->name, name))
    {
      found_callback = current_callback;
      break;
    }
  }
  if (!found_callback)
    return ERR_BUILTIN_NOTFOUND;

  int result = found_callback->func(argv, argc, state);
  if (!result)
    return ERR_BUILTIN_OK;
  else
    return ERR_BUILTIN_ERR;
}

Callback **callback_get_all(CallbackManager *cbm, size_t *cbn)
{
  *cbn = vec_len(cbm->callbacks);
  return (Callback **)vec_data(cbm->callbacks);
}

char *callback_name(Callback *cb)
{
  return cb->name;
}

char *callback_help(Callback *cb)
{
  return cb->help;
}