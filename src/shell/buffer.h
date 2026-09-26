#pragma once

#include <stdint.h>
#include <stddef.h>

#ifndef KIWICON_VECTOR_DEFAULT_CAPACITY
#define KIWICON_VECTOR_DEFAULT_CAPACITY 8
#endif

typedef struct vector_s Vec;

/// @brief Initializes a vector capable of storing items. The default capacity is determined by defining `KIWICON_VECTOR_DEFAULT_CAPACITY`
/// @param item_size Size of each items
/// @return `Vec` which is capable of storing data.
Vec *vec_new(size_t item_size);

/// @brief Frees the vec. Note that the caller is responsible for freeing the data inside the Vec if required.
/// @param vec Pointer to the vec.
void vec_free(Vec *vec);

/// @brief Adds an item to the end of the Vec
/// @param vec Vector to add the item
/// @param item Item to add
void vec_add(Vec *vec, void *item);

/// @brief Returns the internal buffer inside of the vec
/// @param vec
/// @return Pointer to `vec`'s internal buffer
const void *vec_data(Vec *vec);

/// @brief Fetches the length of `vec`
/// @param vec the Vector in question
/// @return The length of `vec` as a `size_t`
size_t vec_len(Vec *vec);