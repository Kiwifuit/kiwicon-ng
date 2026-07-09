#include "buffer.h"

#include <stdlib.h>

struct vector_s
{
  size_t length;
  size_t capacity;
  void **items;
};

Vec *vec_new(size_t item_size)
{
  Vec *vec = malloc(sizeof(Vec));
  if (!vec)
  {
    return NULL;
  }

  void *items = malloc(KIWICON_VECTOR_DEFAULT_CAPACITY * item_size);
  if (!items)
  {
    free(vec);
    return NULL;
  }

  *vec = (Vec){
      .length = 0,
      .capacity = KIWICON_VECTOR_DEFAULT_CAPACITY,
      .items = items};

  return vec;
}

void vec_free(Vec *vec)
{
  free(vec->items);
  free(vec);
  vec = NULL;
}

void vec_resize(Vec *vec)
{
  vec->capacity *= 2;
  vec->items = realloc(vec->items, sizeof(*vec->items) * vec->capacity);
}

void vec_add(Vec *vec, void *item)
{
  if (vec->length + 1 > vec->capacity)
  {
    vec_resize(vec);
  }
  if (item)
  {
    vec->items[vec->length] = item;
    vec->length++;
  }
}

void *vec_data(Vec *vec)
{
  return vec->items;
}

size_t vec_len(Vec *vec)
{
  return vec->length;
}