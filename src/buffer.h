#pragma once

#include <stdint.h>
#include <stddef.h>

#ifndef KIWICON_VECTOR_DEFAULT_CAPACITY
#define KIWICON_VECTOR_DEFAULT_CAPACITY 8
#endif

typedef struct vector_s Vec;

/*
Initializes a vector capable of storing
a couple `item_size`.

The default capacity depends on the
`KIWICON_VECTOR_DEFAULT_CAPACITY` parameter
*/
Vec *vec_new(size_t item_size);

/*
Frees the resources created by this Vec.

NOTE: It is the responsibility of the
callee to free the data inside the Vec
before this function is called. See
`vec_data` and `vec_len` for how the
buffer and its length is to be retrieved
*/
void vec_free(Vec *vec);

/*
Adds an item onto the vector to the
back of the buffer.
*/
void vec_add(Vec *vec, void *item);

/*
Fetches the data inside the Vec
*/
void *vec_data(Vec *vec);

/*
Fetches the length of the Vec
*/
size_t vec_len(Vec *vec);