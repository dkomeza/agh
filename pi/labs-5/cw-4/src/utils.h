#pragma once

struct dumb_vector
{
  int size;
  int capacity;
  int *data;
};

typedef struct dumb_vector dumb_vector_t;

/**
 * A simple dynamic array implementation.
 * It is not thread-safe.
 * It does not handle memory allocation errors.
 * It has a default capacity of 16.
 * It grows by doubling its capacity when it runs out of space.
 * It does not shrink when elements are removed.
 * It supports negative indices.
 */
struct dumb_vector *create_dumb_vector(int capacity);
void destroy_dumb_vector(struct dumb_vector *v);
void push_back(struct dumb_vector *v, int value);
int get(struct dumb_vector *v, int index);
void set(struct dumb_vector *v, int index, int value);
int size(struct dumb_vector *v);
int capacity(struct dumb_vector *v);
int is_empty(struct dumb_vector *v);
int is_full(struct dumb_vector *v);
